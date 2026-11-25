#!/usr/bin/env python3
"""Team 6: two-stage RED/GREEN/YELLOW bin detection (experimental).

Separate from the stable block detector; uses RealSense colour and aligned
depth topics. From farther away, finds a COLOURED BIN BODY (coarse candidate,
not a drop point). When close and the aperture is visible, fits a four-sided
opening and estimates its rim-plane XYZ (experimental).

Publishes EXPERIMENTAL diagnostics only:
  /vision/bins/debug_json            std_msgs/msg/String (JSON diagnostics)
  /vision/bins/red/debug_point       geometry_msgs/msg/PointStamped
  /vision/bins/green/debug_point     geometry_msgs/msg/PointStamped
  /vision/bins/yellow/debug_point    geometry_msgs/msg/PointStamped

Points use the incoming RGB frame (normally camera_color_optical_frame), NOT
base_link. NO /vision/bins control interface and NO robot-arm commands.
Plane-fit residual is NOT verified absolute positioning accuracy.

Usage:
  python3 bin_opening_rgy.py
  python3 bin_opening_rgy.py --image sample.jpg --output result.png
Press Q or Escape to close the live view.
"""
import argparse
import json
import time

import cv2
import numpy as np

VERSION = 'RGY-bin-body-then-opening-v4-2026-11-18'
RGB_TOPIC = '/camera/camera/color/image_raw'
DEPTH_TOPIC = '/camera/camera/aligned_depth_to_color/image_raw'
INFO_TOPIC = '/camera/camera/color/camera_info'
DEBUG_JSON_TOPIC = '/vision/bins/debug_json'
WINDOW = 'LeoRover RGY BIN OPENINGS (experimental) | Q: quit'

COLOURS = ('Red', 'Green', 'Yellow')
# BGR visualization colours
DRAW_COLOURS = {'Red': (0, 0, 255),
                'Green': (0, 235, 0),
                'Yellow': (0, 230, 255)}
# Colour ranges are intentionally broad for painted bins; the closed-hole
# test prevents small coloured blocks from being classified as bins.
# Tune these on REAL green/yellow bins if different paints are used.
HSV_RANGES = {
    'Red': [((0, 75, 45), (12, 255, 255)),
            ((169, 75, 45), (179, 255, 255))],
    'Green': [((38, 55, 35), (106, 255, 255))],
    'Yellow': [((18, 95, 65), (38, 255, 255))],
}

MIN_Z, MAX_Z = 0.20, 1.50     # Valid depth for accurate opening plane
BODY_MAX_Z = 3.0              # Coarse coloured-body recognition at longer range
DEFAULT_OPENING_RANGE_M = 1.15  # Try precise opening once the body is near
# Loose silhouette thresholds distinguish 20cm-class bins from 2/6cm blocks.
# Approximations from perspective, not a measured bin dimension.
MIN_BODY_LONG_M = 0.100
MIN_BODY_SHORT_M = 0.052
MAX_STAMP_GAP_S = 0.08
RIM_MIN_SAMPLES = 45
PLANE_TOLERANCE_M = 0.010
RANSAC_TRIALS = 85


def colour_mask(frame, colour, hsv=None):
    """Segment the bin paint, NOT the hole (hole is generally non-coloured)."""
    if hsv is None:
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    mask = np.zeros(hsv.shape[:2], dtype=np.uint8)
    for low, high in HSV_RANGES[colour]:
        mask |= cv2.inRange(hsv, np.array(low, dtype=np.uint8),
                            np.array(high, dtype=np.uint8))
    if colour == 'Green':
        # Exclude cyan/blue screens with little green contrast to red.
        b, g, r = cv2.split(frame)
        g, r, b = g.astype(np.int16), r.astype(np.int16), b.astype(np.int16)
        # Both true green (low B) and turquoise-green (high B) are valid.
        mask = cv2.bitwise_and(mask, ((g-r >= 12) & (g-b >= -28)).astype(np.uint8)*255)
    close_size = 9 if colour == 'Green' else 7
    mask = cv2.morphologyEx(mask, cv2.MORPH_CLOSE,
                            cv2.getStructuringElement(cv2.MORPH_ELLIPSE,
                                                      (close_size, close_size)))
    mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN,
                            cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (3, 3)))
    return mask


def perspective_centre(quad):
    """Intersection of diagonals (planar opening centre under perspective)."""
    a, b, c, d = np.asarray(quad, dtype=float).reshape((4, 2))
    r, s = c-a, d-b
    denominator = float(r[0]*s[1] - r[1]*s[0])
    if abs(denominator) < 1e-8:
        return None
    ba = b-a
    t = float(ba[0]*s[1] - ba[1]*s[0]) / denominator
    centre = a+t*r
    if not np.all(np.isfinite(centre)):
        return None
    return tuple(float(x) for x in centre)


def _extract_openings(mask, merge_fragments=False):
    """Extract four-cornered holes; optional merger of adjacent hole fragments.

    At an oblique view the brown interior of a yellow box can be partially
    classified as yellow. This splits one opening into several enclosed dark
    regions. The fallback joins nearby holes inside the SAME coloured contour.
    Never extrapolate a hole that runs out of the camera image.
    """
    h, w = mask.shape
    contours, hierarchy = cv2.findContours(mask, cv2.RETR_TREE,
                                           cv2.CHAIN_APPROX_SIMPLE)
    if hierarchy is None:
        return None
    hierarchy = hierarchy[0]
    outer_min = max(1500, 0.015*w*h)
    hole_min = max(500, 0.005*w*h)
    best = None

    for i, outer in enumerate(contours):
        if hierarchy[i][3] != -1:
            continue
        outer_area = cv2.contourArea(outer)
        if outer_area < outer_min:
            continue
        ox, oy, ow, oh = cv2.boundingRect(outer)
        children = []
        child = hierarchy[i][2]
        while child >= 0:
            hole = contours[child]
            ha = cv2.contourArea(hole)
            if ha >= (max(250, 0.001*w*h) if merge_fragments else hole_min):
                children.append((ha, hole))
            child = hierarchy[child][0]
        children.sort(key=lambda x: x[0], reverse=True)
        if not children:
            continue

        candidate_holes = []
        if not merge_fragments:
            candidate_holes = [(hole, ha) for ha, hole in children]
        else:
            # Only bridge sizeable neighbouring internal HOLE fragments.
            # Do not join openings belonging to different outer colour blobs.
            largest_a, largest = children[0]
            x0, y0, bw, bh = cv2.boundingRect(largest)
            fragments = [largest]
            for ha, hole in children[1:]:
                if ha < max(700, 0.25 * largest_a):
                    continue
                x, y, cw, ch = cv2.boundingRect(hole)
                margin = 18
                if (x <= x0 + bw + margin and x + cw >= x0 - margin and
                        y <= y0 + bh + margin and y + ch >= y0 - margin and
                        y + ch/2 < oy + 0.70*oh):
                    fragments.append(hole)
            combined = cv2.convexHull(np.vstack(fragments))
            candidate_holes = [(combined, cv2.contourArea(combined))]

        for hole, ha in candidate_holes:
            ratio = ha / max(outer_area, 1.0)
            if ha < hole_min or not 0.045 < ratio < 0.78:
                continue
            hull = cv2.convexHull(hole)
            perimeter = cv2.arcLength(hull, True)
            quad = None
            for eps in (0.02, 0.03, 0.04, 0.05, 0.065, 0.08):
                polygon = cv2.approxPolyDP(hull, eps * perimeter, True)
                if (len(polygon) == 4 and
                        cv2.isContourConvex(polygon) and
                        cv2.contourArea(polygon) >= 0.70*ha):
                    quad = polygon.reshape(4, 2)
                    break
            if quad is None:
                continue
            centre = perspective_centre(quad)
            if centre is None:
                continue
            u, v = centre
            # A complete, visible opening is necessary for a placement target.
            if (min(quad[:, 0]) < 5 or max(quad[:, 0]) >= w-5 or
                    min(quad[:, 1]) < 5 or max(quad[:, 1]) >= h-5 or
                    not (5 <= u < w-5 and 5 <= v < h-5)):
                continue
            candidate = dict(quad=quad, centre_uv=centre, hole=hull,
                             hole_area_px=ha, outer_area_px=outer_area,
                             hole_ratio=ratio,
                             method=('merged-rim' if merge_fragments
                                     else 'closed-hole'))
            if best is None or ha > best['hole_area_px']:
                best = candidate
    return best


def find_bin_opening(frame, colour, hsv=None, mask=None):
    """Find bin aperture with a low-cost fallback for oblique painted rims.

    Normal detection is unchanged. When the visible hole is unusually small
    relative to the bin's coloured silhouette (or missing), retry with a
    brighter rim mask and merge adjacent enclosed dark-hole fragments.
    A cropped/unseen opening is NOT guessed and stays undetected.
    """
    if hsv is None:
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    if mask is None:
        mask = colour_mask(frame, colour, hsv=hsv)
    base = _extract_openings(mask)
    # 0.09 corresponds to an unusually small opening relative to the
    # coloured silhouette; this may be a partially merged/occluded hole.
    if base is not None and base['hole_ratio'] >= 0.09:
        return base, mask

    # A cheap value-channel fallback separates bright painted rims from the
    # darker bin interior. Different paint colours need different thresholds.
    min_value = {'Red': 125, 'Green': 105, 'Yellow': 135}[colour]
    bright_mask = cv2.bitwise_and(
        mask, ((hsv[:, :, 2] >= min_value).astype(np.uint8) * 255))
    bright_mask = cv2.morphologyEx(
        bright_mask, cv2.MORPH_CLOSE,
        cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (9, 9)))
    fallback = _extract_openings(bright_mask, merge_fragments=True)
    # Conservative size guard: coloured laptop screens, small stickers or
    # random highlights must not be treated as a physical storage-bin opening.
    h, w = mask.shape
    if (fallback is not None and
            fallback['hole_area_px'] >= max(3500, 0.012*w*h) and
            (base is None or
             fallback['hole_area_px'] > 1.25 * base['hole_area_px'])):
        return fallback, bright_mask

    # Prefer the original rim geometry whenever it is sufficiently plausible.
    if base is not None and base['hole_ratio'] >= 0.075:
        return base, mask

    # RED-SPECIFIC recovery for oblique views: the reddish interior can pass
    # the basic red hue mask, filling in the opening. In these images the
    # painted rim is usually more saturated than the interior. Use the same
    # HSV colour mask but require a stronger S component to expose the hole.
    # This is a fallback only: do not disturb already-good red, green or
    # yellow detections. Reject edge-clipped holes and very small regions in
    # _extract_openings; the point is never published for unseen openings.
    if colour == 'Red':
        sat_mask = cv2.bitwise_and(
            mask, cv2.inRange(hsv[:, :, 1], 160, 255))
        sat_mask = cv2.morphologyEx(
            sat_mask, cv2.MORPH_CLOSE,
            cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (7, 7)))
        sat_opening = _extract_openings(sat_mask)
        h, w = mask.shape
        if (sat_opening is not None and
                sat_opening['hole_area_px'] >= max(2500, 0.008*w*h) and
                sat_opening['hole_ratio'] >= 0.06):
            sat_opening['method'] = 'red-saturation'
            return sat_opening, sat_mask

    # Recover green openings where dim paint or a thin break in the rim
    # prevents a closed-hole contour. Retain the original algorithm first.
    if colour == 'Green':
        kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (15, 15))
        sealed = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, kernel)
        green_opening = _extract_openings(sealed)
        h, w = mask.shape
        if (green_opening is not None and
                green_opening['hole_area_px'] >= max(2200, 0.007*w*h) and
                green_opening['hole_ratio'] >= 0.065):
            green_opening['method'] = 'green-sealed-rim'
            return green_opening, sealed
        # The green front face may be dark while the upper rim stays brighter.
        # Use a frame-relative V threshold instead of only a fixed threshold.
        values = hsv[:, :, 2][mask > 0]
        if len(values) >= 500:
            adaptive_v = int(np.clip(np.percentile(values, 54), 68, 125))
            brighter = cv2.bitwise_and(
                mask, cv2.inRange(hsv[:, :, 2], adaptive_v, 255))
            brighter = cv2.morphologyEx(brighter, cv2.MORPH_CLOSE, kernel)
            green_opening = _extract_openings(brighter, merge_fragments=True)
            if (green_opening is not None and
                    green_opening['hole_area_px'] >= max(2800, 0.009*w*h) and
                    green_opening['hole_ratio'] >= 0.065):
                green_opening['method'] = 'green-adaptive-rim'
                return green_opening, brighter

    # Reject tiny apparent holes; a visible side wall alone must never yield
    # a guessed drop target.
    return None, mask



def _body_depth_and_size(depth, encoding, intrinsics, mask, contour):
    """Median coloured-surface depth and loose perspective size in metres.

    The returned xyz is a *surface observation*, NOT the bin's geometric centre
    and NEVER a release pose. Subsample mask pixels to control CPU cost.
    """
    if depth is None or intrinsics is None or depth.shape[:2] != mask.shape:
        return None
    fx, fy, cx, cy = map(float, intrinsics)
    if min(fx, fy) <= 0 or encoding not in ('16UC1', '32FC1'):
        return None
    x, y, w, h = cv2.boundingRect(contour)
    cmask = np.zeros((h, w), dtype=np.uint8)
    shifted = contour.copy()
    shifted[:, :, 0] -= x
    shifted[:, :, 1] -= y
    cv2.drawContours(cmask, [shifted], -1, 255, thickness=-1)
    cmask = cv2.bitwise_and(cmask, mask[y:y+h, x:x+w])
    ys, xs = np.nonzero(cmask[::3, ::3])
    if len(xs) < 15:
        return None
    us = xs*3 + x
    vs = ys*3 + y
    zs = depth[vs, us].astype(np.float64)
    if encoding == '16UC1':
        zs *= 0.001
    ok = np.isfinite(zs) & (zs >= MIN_Z) & (zs <= BODY_MAX_Z)
    if np.count_nonzero(ok) < 15:
        return None
    us, vs, zs = us[ok], vs[ok], zs[ok]
    z = float(np.median(zs))
    # Body surface observation is deliberately named differently from
    # the opening-centre XYZ. It cannot be reused for placing a block.
    u, v = float(np.median(us)), float(np.median(vs))
    xyz = ((u-cx)*z/fx, (v-cy)*z/fy, z)
    ra, rb = cv2.minAreaRect(contour)[1]
    longer, shorter = sorted((float(ra), float(rb)), reverse=True)
    focal = np.sqrt(fx*fy)
    return dict(depth_m=z, surface_xyz_m=tuple(map(float, xyz)),
                long_m=longer*z/focal, short_m=shorter*z/focal)


def find_bin_body(frame, colour, depth=None, encoding=None,
                  intrinsics=None, mask=None):
    """Find a sizeable coloured bin silhouette even when aperture unseen.

    Return a conservative coloured BODY candidate for navigation/search only.
    Never extrapolate or claim an opening from a partial or hidden silhouette.
    """
    if mask is None:
        mask = colour_mask(frame, colour)
    if colour == 'Green':
        # Coarse green BODY needs a stricter hue than the opening search.
        # Blue-tinted laptop screens often have H~100; real green paint in
        # provided tests lies mostly H~65-90. Keep the opening mask broad.
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        b, g, r = cv2.split(frame)
        b, g, r = b.astype(np.int16), g.astype(np.int16), r.astype(np.int16)
        green_body = cv2.inRange(hsv, (38, 90, 35), (94, 255, 255))
        green_body &= (((g-r) >= 12) & ((g-b) >= -18)).astype(np.uint8)*255
        mask = cv2.morphologyEx(green_body, cv2.MORPH_CLOSE,
                     cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (9, 9)))
    h, w = mask.shape
    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL,
                                   cv2.CHAIN_APPROX_SIMPLE)
    candidates = []
    for c in contours:
        area = cv2.contourArea(c)
        # Low area floor allows bins seen from farther away; depth-based
        # size rejection below keeps 2cm and 6cm blocks out of BODY mode.
        if area < max(260, 0.0009*w*h):
            continue
        x, y, bw, bh = cv2.boundingRect(c)
        if bw < 23 or bh < 22:
            continue
        rotated = cv2.minAreaRect(c)[1]
        if min(rotated) < 14:
            continue
        if area / max(1, bw*bh) < 0.18:
            continue
        depth_info = _body_depth_and_size(depth, encoding, intrinsics, mask, c)
        if depth_info is not None:
            if (depth_info['long_m'] < MIN_BODY_LONG_M or
                    depth_info['short_m'] < MIN_BODY_SHORT_M):
                continue
        else:
            # Without a valid depth estimate, avoid claiming a small colour
            # patch as a bin. 2D candidate is debug-only, never navigation XYZ.
            if area < max(1900, 0.006*w*h) or bw < 55 or bh < 42:
                continue
        candidates.append((area, c, (x, y, bw, bh), depth_info))
    if not candidates:
        return None
    area, contour, bbox, info = max(candidates, key=lambda x: x[0])
    x, y, bw, bh = bbox
    m = cv2.moments(contour)
    u = float(m['m10']/m['m00']) if m['m00'] else x+bw/2
    v = float(m['m01']/m['m00']) if m['m00'] else y+bh/2
    return dict(bbox=bbox, contour=contour, centre_uv=(u, v),
                area_px=area, depth_info=info,
                clipped=(x < 5 or y < 5 or x+bw >= w-5 or y+bh >= h-5))


def rim_plane_centre(depth, encoding, intrinsics, mask, opening):
    """Estimate 3D opening-centre on the rim plane, NOT bin's interior floor.

    Uses RANSAC on depth from a narrow coloured annulus outside the hole;
    returns (camera_xyz, support_fraction, plane_rms_metres) or None.
    Note: this tests local planar consistency, NOT absolute geometric accuracy.
    """
    if depth is None or intrinsics is None or opening is None:
        return None
    if depth.shape[:2] != mask.shape:
        return None
    fx, fy, cx, cy = map(float, intrinsics)
    if fx <= 0 or fy <= 0:
        return None
    h, w = depth.shape[:2]
    hole_mask = np.zeros((h, w), dtype=np.uint8)
    cv2.drawContours(hole_mask, [opening['hole']], -1, 255, thickness=-1)
    outer_band = cv2.dilate(hole_mask, cv2.getStructuringElement(
        cv2.MORPH_ELLIPSE, (27, 27)))
    inner_band = cv2.dilate(hole_mask, cv2.getStructuringElement(
        cv2.MORPH_ELLIPSE, (7, 7)))
    band = cv2.bitwise_and(cv2.subtract(outer_band, inner_band), mask)
    vs, us = np.nonzero(band[::2, ::2])
    us, vs = (us*2).astype(np.int32), (vs*2).astype(np.int32)
    if len(us) < RIM_MIN_SAMPLES:
        return None
    z = depth[vs, us].astype(np.float64)
    if encoding == '16UC1':
        z *= 0.001
    elif encoding != '32FC1':
        return None
    valid = np.isfinite(z) & (MIN_Z <= z) & (z <= MAX_Z)
    if int(np.count_nonzero(valid)) < RIM_MIN_SAMPLES:
        return None
    us, vs, z = us[valid], vs[valid], z[valid]
    points = np.column_stack(((us-cx)*z/fx, (vs-cy)*z/fy, z))
    if len(points) > 480:
        points = points[np.linspace(0, len(points)-1, 480, dtype=int)]
    rng = np.random.default_rng(11)
    best_inliers = np.zeros(len(points), dtype=bool)
    for _ in range(RANSAC_TRIALS):
        a, b, c = points[rng.choice(len(points), 3, replace=False)]
        normal = np.cross(b-a, c-a)
        norm = np.linalg.norm(normal)
        if norm < 1e-8:
            continue
        normal /= norm
        inliers = np.abs((points-a) @ normal) < PLANE_TOLERANCE_M
        if np.count_nonzero(inliers) > np.count_nonzero(best_inliers):
            best_inliers = inliers
    support = float(np.mean(best_inliers))
    if int(np.count_nonzero(best_inliers)) < RIM_MIN_SAMPLES or support < 0.58:
        return None
    p = points[best_inliers]
    centroid = np.mean(p, axis=0)
    _, _, vt = np.linalg.svd(p-centroid, full_matrices=False)
    normal = vt[-1]
    rms = float(np.sqrt(np.mean(((p-centroid) @ normal)**2)))
    if rms > 0.008:
        return None
    u, v = opening['centre_uv']
    ray = np.array([(u-cx)/fx, (v-cy)/fy, 1.0])
    denominator = float(normal @ ray)
    if abs(denominator) < 0.10:
        return None
    zcentre = float(normal @ centroid / denominator)
    if not MIN_Z <= zcentre <= MAX_Z:
        return None
    return tuple(float(q) for q in ray*zcentre), support, rms


def annotate(frame, results):
    """Draw one body or opening per colour, with unobstructed status labels."""
    drawn = frame.copy()
    h, w = drawn.shape[:2]
    cv2.rectangle(drawn, (0, 0), (w, 74), (0, 0, 0), -1)
    cv2.putText(drawn, VERSION, (8, 17), cv2.FONT_HERSHEY_SIMPLEX,
                0.46, (255, 255, 255), 1, cv2.LINE_AA)
    summary = []
    bottom_lines = []
    for colour in COLOURS:
        res = results[colour]
        body, opening, xyz_info = res['body'], res['opening'], res['xyz_info']
        col = DRAW_COLOURS[colour]
        if body is None and opening is None:
            summary.append(f'{colour[0]}:--')
            bottom_lines.append((col, f'{colour}: not visible'))
            continue
        if opening is None:
            summary.append(f'{colour[0]}:BODY')
            x, y, bw, bh = body['bbox']
            cv2.rectangle(drawn, (x, y), (x+bw, y+bh), col, 2, cv2.LINE_AA)
            info = body['depth_info']
            dist = f"~{info['depth_m']:.2f}m" if info is not None else 'no depth'
            bottom_lines.append((col, f'{colour}: BODY {dist} | search only'))
        else:
            quad = opening['quad'].reshape((-1, 1, 2))
            cv2.polylines(drawn, [quad], True, col, 3, cv2.LINE_AA)
            u, v = opening['centre_uv']
            cv2.drawMarker(drawn, (int(round(u)), int(round(v))),
                           (255, 255, 255), cv2.MARKER_CROSS, 18, 2, cv2.LINE_AA)
            if xyz_info is not None:
                xyz, _, _ = xyz_info
                summary.append(f'{colour[0]}:3D')
                bottom_lines.append((col, f'{colour}: OPEN 3D  X{xyz[0]:+.2f} '
                                             f'Y{xyz[1]:+.2f} Z{xyz[2]:.2f}m'))
            else:
                summary.append(f'{colour[0]}:2D')
                bottom_lines.append((col, f'{colour}: OPEN 2D | no safe XYZ'))
    cv2.putText(drawn, 'BINS: '+'  '.join(summary)+' | Debug only',
                (8, 43), cv2.FONT_HERSHEY_SIMPLEX,
                0.51, (255, 255, 255), 1, cv2.LINE_AA)
    cv2.putText(drawn, 'BODY=search; OPEN=opening visible; no arm commands',
                (8, 63), cv2.FONT_HERSHEY_SIMPLEX,
                0.38, (210, 210, 210), 1, cv2.LINE_AA)
    # Place three diagnostic rows above the real-time sync statistic at bottom.
    # Text cannot overlap nearby bin openings at the top of the image.
    panel_y = max(74, h-101)
    overlay = drawn.copy()
    cv2.rectangle(overlay, (0, panel_y), (w, h-27), (0, 0, 0), -1)
    drawn = cv2.addWeighted(overlay, 0.58, drawn, 0.42, 0)
    for i, (col, message) in enumerate(bottom_lines):
        cv2.putText(drawn, message, (8, panel_y+20+i*20),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.47, col, 1, cv2.LINE_AA)
    return drawn


def detect_all(frame, depth=None, encoding=None, intrinsics=None,
               opening_range_m=DEFAULT_OPENING_RANGE_M):
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    results = {}
    for colour in COLOURS:
        mask = colour_mask(frame, colour, hsv=hsv)
        body = find_bin_body(frame, colour, depth, encoding, intrinsics, mask)
        # A body far away must not trigger an unreliable opening/placement
        # estimate. If body depth is unknown, still allow 2D opening detection
        # so offline photographs remain useful for debugging.
        far = (body is not None and body['depth_info'] is not None and
               body['depth_info']['depth_m'] > opening_range_m)
        opening, rim_mask = (None, mask) if far else find_bin_opening(
            frame, colour, hsv=hsv, mask=mask)
        xyz_info = rim_plane_centre(depth, encoding, intrinsics,
                                    rim_mask, opening)
        stage = ('opening_3d' if xyz_info is not None else
                 'opening_2d' if opening is not None else
                 'body_only' if body is not None else 'not_found')
        results[colour] = dict(body=body, opening=opening,
                               xyz_info=xyz_info, stage=stage)
    return results


def run_ros(max_fps=15.0, opening_range_m=DEFAULT_OPENING_RANGE_M):
    """Low-latency ROS2 input: timestamp-paired messages, latest-pair wins.

    ROS subscriptions spin in a short-callback background thread. The main
    thread performs computer vision and OpenCV GUI work. Slow processing will
    discard superseded PAIRS rather than build a queue of stale observations.
    """
    import threading

    import rclpy
    from cv_bridge import CvBridge
    from geometry_msgs.msg import PointStamped
    from rclpy.node import Node
    from rclpy.qos import (
        qos_profile_sensor_data, QoSProfile, ReliabilityPolicy,
        DurabilityPolicy,
    )
    from sensor_msgs.msg import CameraInfo, Image
    from std_msgs.msg import String
    from message_filters import Subscriber, ApproximateTimeSynchronizer

    class RGYBinOpeningDetector(Node):
        def __init__(self):
            super().__init__('rgy_bin_openings_debug')
            self.bridge = CvBridge()
            self.lock = threading.Lock()
            self.newest_pair = None
            self.pair_count = 0
            self.seen_pairs = 0
            self.last_pair_monotonic = None
            self.k = None
            self.summary_pub = self.create_publisher(String, DEBUG_JSON_TOPIC, 10)
            self.point_pubs = {
                c: self.create_publisher(PointStamped,
                    f'/vision/bins/{c.lower()}/debug_point', 10)
                for c in COLOURS
            }
            # RELIABLE is important on this NUC: benchmarked ~15Hz per stream
            # instead of 0.5-1Hz with BEST_EFFORT. Keep VOLATILE history.
            image_qos = QoSProfile(
                depth=5, reliability=ReliabilityPolicy.RELIABLE,
                durability=DurabilityPolicy.VOLATILE)
            self.rgb_sub = Subscriber(self, Image, RGB_TOPIC,
                                      qos_profile=image_qos)
            self.depth_sub = Subscriber(self, Image, DEPTH_TOPIC,
                                        qos_profile=image_qos)
            self.sync = ApproximateTimeSynchronizer(
                [self.rgb_sub, self.depth_sub], queue_size=16,
                slop=MAX_STAMP_GAP_S)
            self.sync.registerCallback(self.on_pair)
            self.info_sub = self.create_subscription(
                CameraInfo, INFO_TOPIC, self.on_info, qos_profile_sensor_data)
            self.get_logger().info(
                'Low-latency RGY bins: synced pairs, latest-only, experimental; '
                'no arm commands. Start RealSense with enable_sync:=true.')

        def on_pair(self, rgb, depth):
            # Never decode images or do vision in a ROS subscriber callback.
            if rgb.width != depth.width or rgb.height != depth.height:
                return
            now = time.monotonic()
            with self.lock:
                self.pair_count += 1
                self.newest_pair = (rgb, depth, self.k, now, self.pair_count)
                self.last_pair_monotonic = now

        def on_info(self, msg):
            k = msg.k
            if k[0] > 0 and k[4] > 0:
                with self.lock:
                    self.k = (k[0], k[4], k[2], k[5])

        @staticmethod
        def stamp_s(msg):
            return (float(msg.header.stamp.sec)
                    + 1e-9*float(msg.header.stamp.nanosec))

        def take_latest(self):
            with self.lock:
                result = self.newest_pair
                self.newest_pair = None
                count = self.pair_count
            return result, count

        def publish(self, rgb_msg, results):
            payload = {
                'experimental': True,
                'camera_frame_id': rgb_msg.header.frame_id,
                'stamp': {'sec': rgb_msg.header.stamp.sec,
                          'nanosec': rgb_msg.header.stamp.nanosec},
                'bins': []
            }
            for colour, res in results.items():
                body, opening, xyz_info = (res['body'], res['opening'],
                                           res['xyz_info'])
                if body is None and opening is None:
                    continue
                entry = {'color': colour.lower(),
                         'stage': res['stage'],
                         'valid_3d': xyz_info is not None,
                         'opening_center_uv': None,
                         'body_center_uv': None}
                if body is not None:
                    entry['body_center_uv'] = [round(v, 1)
                                               for v in body['centre_uv']]
                    entry['body_bbox_xywh'] = list(body['bbox'])
                    entry['body_clipped'] = bool(body['clipped'])
                    if body['depth_info'] is not None:
                        info = body['depth_info']
                        entry['body_surface_xyz_m'] = list(info['surface_xyz_m'])
                        entry['body_surface_depth_m'] = info['depth_m']
                        # No point topic for body: not an arm drop target.
                if opening is not None:
                    entry['opening_center_uv'] = [round(v, 1)
                                                  for v in opening['centre_uv']]
                    entry['opening_method'] = opening.get('method', 'closed-hole')
                if xyz_info is not None:
                    xyz, support, rms = xyz_info
                    entry.update({'center_xyz_m': list(xyz),
                                  'plane_support': support,
                                  'plane_rms_m': rms})
                    point = PointStamped()
                    point.header = rgb_msg.header
                    point.point.x, point.point.y, point.point.z = xyz
                    self.point_pubs[colour].publish(point)
                payload['bins'].append(entry)
            msg = String()
            msg.data = json.dumps(payload, separators=(',', ':'))
            self.summary_pub.publish(msg)

    rclpy.init()
    node = None
    spin_thread = None
    try:
        node = RGYBinOpeningDetector()
        spin_thread = threading.Thread(target=rclpy.spin, args=(node,),
                                       daemon=True, name='rgy-bin-ros-spin')
        spin_thread.start()
        processed_count = 0
        skipped_stale = 0
        last_report_time = time.monotonic()
        last_process_time = 0.0
        last_seen_id = 0
        report_pairs = 0
        report_processed = 0
        wait_warn_time = time.monotonic()
        min_interval = 1.0/max(1.0, max_fps)

        while rclpy.ok():
            key = cv2.waitKey(1) & 0xff
            if key in (ord('q'), 27):
                break
            now = time.monotonic()
            # Cap processing rate without delaying subscriptions or GUI input.
            if now - last_process_time >= min_interval:
                latest, pair_count = node.take_latest()
                if latest is not None:
                    rgb_msg, depth_msg, intrinsics, received_at, pair_id = latest
                    if pair_id > last_seen_id + 1:
                        skipped_stale += pair_id - last_seen_id - 1
                    last_seen_id = pair_id
                    # Don't process a queued pair that has already become old.
                    if now-received_at > 0.35:
                        skipped_stale += 1
                    elif intrinsics is not None:
                        try:
                            frame = node.bridge.imgmsg_to_cv2(
                                rgb_msg, desired_encoding='bgr8')
                            depth = node.bridge.imgmsg_to_cv2(
                                depth_msg, desired_encoding='passthrough')
                            results = detect_all(frame, depth,
                                                 depth_msg.encoding, intrinsics,
                                                 opening_range_m)
                            output = annotate(frame, results)
                            gap_ms = 1000*abs(node.stamp_s(rgb_msg)
                                              - node.stamp_s(depth_msg))
                            cv2.putText(output,
                                f'Synced RGB-D | gap {gap_ms:.0f}ms | '
                                f'cap {max_fps:g}Hz | drops {skipped_stale}',
                                (8, max(78, frame.shape[0]-12)),
                                cv2.FONT_HERSHEY_SIMPLEX, 0.45,
                                (255, 255, 255), 1, cv2.LINE_AA)
                            cv2.imshow(WINDOW, output)
                            node.publish(rgb_msg, results)
                            processed_count += 1
                            last_process_time = time.monotonic()
                        except Exception as exc:
                            node.get_logger().warning(
                                f'Frame processing error: {exc}')
                elif now - wait_warn_time >= 5 and processed_count == 0:
                    node.get_logger().warning(
                        'No synced RGB/depth frames received. '
                        'Restart camera with enable_sync:=true and check topics.')
                    wait_warn_time = now
            if now-last_report_time >= 5:
                total_pairs = node.pair_count
                dt = max(1e-3, now-last_report_time)
                node.get_logger().info(
                    f'SYNC {((total_pairs-report_pairs)/dt):.1f} Hz, '
                    f'DETECT {((processed_count-report_processed)/dt):.1f} Hz, '
                    f'skipped older pairs {skipped_stale}')
                report_pairs, report_processed = total_pairs, processed_count
                last_report_time = now
            time.sleep(0.004)
    except KeyboardInterrupt:
        pass
    finally:
        if rclpy.ok():
            rclpy.shutdown()
        if spin_thread is not None:
            spin_thread.join(timeout=2)
        if node is not None:
            node.destroy_node()
        cv2.destroyAllWindows()


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--image', help='Offline RGB image, no RealSense needed')
    parser.add_argument('--opening-range', type=float, default=DEFAULT_OPENING_RANGE_M,
                        help='Max coarse body depth for attempting opening XYZ (default 1.15m)')
    parser.add_argument('--output', help='Where to save annotated offline image')
    parser.add_argument('--max-fps', type=float, default=15.0,
                        help='Maximum detection iterations per second (default: 15)')
    args = parser.parse_args()
    if args.image:
        frame = cv2.imread(args.image)
        if frame is None:
            parser.error('Cannot open input image')
        results = detect_all(frame, opening_range_m=args.opening_range)
        result_path = args.output or 'bin_openings_rgy_debug.png'
        if not cv2.imwrite(result_path, annotate(frame, results)):
            parser.error(f'Cannot write {result_path}')
        print('Version:', VERSION)
        for colour, res in results.items():
            print(f'{colour}: {res["stage"]}',
                  f"opening UV={res['opening']['centre_uv']}" if res['opening'] else
                  f"body UV={res['body']['centre_uv']}" if res['body'] else '')
        print('Annotated image:', result_path)
    else:
        run_ros(max_fps=args.max_fps, opening_range_m=args.opening_range)

if __name__ == '__main__':
    main()
