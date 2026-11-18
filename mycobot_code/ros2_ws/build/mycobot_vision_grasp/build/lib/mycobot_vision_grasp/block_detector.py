"""Block detection (OpenCV / numpy only, no ROS dependency, testable on its own).

Steps:
  1. Segment blocks from the background with HSV colour thresholds
  2. Fit minAreaRect to each contour to get the 4 corners of the minimum-area rectangle
     (= the block's two pairs of parallel edges)
  3. Read the top-face depth from the depth image and deproject the centre and corners
     into 3D points in the camera frame
"""
from dataclasses import dataclass, field

import cv2
import numpy as np


@dataclass
class BlockDetection:
    center_px: np.ndarray          # (2,) rectangle centre pixel (u, v)
    corners_px: np.ndarray         # (4, 2) rectangle corners, in order
    center_depth: float            # top-face centre depth [m]
    corner_depths: np.ndarray      # (4,) top-face depth near each corner [m]
    area_px: float                 # contour area [pixel^2]
    contour: np.ndarray = field(repr=False, default=None)


def depth_to_meters(depth):
    """Gazebo depth images are 32FC1 (metres); a real RealSense is usually 16UC1 (millimetres).
    Convert both to metres."""
    d = np.asarray(depth)
    if d.dtype == np.uint16:
        d = d.astype(np.float32) * 0.001
    else:
        d = d.astype(np.float32).copy()
    d[~np.isfinite(d)] = 0.0
    return d


def make_mask(bgr, hsv_ranges, kernel_size=5):
    """hsv_ranges: [((h,s,v)_low, (h,s,v)_high), ...]. Red needs two ranges (H near 0 and 180)."""
    hsv = cv2.cvtColor(bgr, cv2.COLOR_BGR2HSV)
    mask = np.zeros(hsv.shape[:2], np.uint8)
    for lo, hi in hsv_ranges:
        mask |= cv2.inRange(hsv, np.array(lo, np.uint8), np.array(hi, np.uint8))
    k = cv2.getStructuringElement(cv2.MORPH_RECT, (kernel_size, kernel_size))
    mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, k)
    mask = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, k)
    return mask


def _median_valid(values, dmin, dmax):
    v = values[(values > dmin) & (values < dmax)]
    return float(np.median(v)) if v.size else float('nan')


def detect_blocks(bgr, depth, hsv_ranges, min_area=200, max_area=1e7,
                  depth_range=(0.03, 3.0), corner_inset=0.3):
    """Returns (detections, mask). Detections are sorted by area, largest first."""
    depth_m = depth_to_meters(depth)
    if depth_m.shape[:2] != bgr.shape[:2]:
        depth_m = cv2.resize(depth_m, (bgr.shape[1], bgr.shape[0]),
                             interpolation=cv2.INTER_NEAREST)
    dmin, dmax = depth_range
    mask = make_mask(bgr, hsv_ranges)
    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    h, w = mask.shape
    erode_k = np.ones((5, 5), np.uint8)

    detections = []
    for c in contours:
        area = cv2.contourArea(c)
        if area < min_area or area > max_area:
            continue
        rect = cv2.minAreaRect(c)
        box = cv2.boxPoints(rect).astype(np.float64)
        center = np.array(rect[0], np.float64)

        # Sample depth only inside the block (eroded, to avoid depth jumps at the edges)
        single = np.zeros_like(mask)
        cv2.drawContours(single, [c], -1, 255, -1)
        inner = cv2.erode(single, erode_k)
        if not inner.any():
            inner = single
        cd = _median_valid(depth_m[inner > 0], dmin, dmax)
        if not np.isfinite(cd):
            continue

        # Sample local depth at each corner moved towards the centre, to handle a tilted camera
        corner_depths = []
        for p in box:
            q = center + (1.0 - corner_inset) * (p - center)
            u, v = int(round(q[0])), int(round(q[1]))
            u0, u1 = max(u - 3, 0), min(u + 4, w)
            v0, v1 = max(v - 3, 0), min(v + 4, h)
            win = depth_m[v0:v1, u0:u1][inner[v0:v1, u0:u1] > 0]
            d = _median_valid(win, dmin, dmax) if win.size else float('nan')
            corner_depths.append(d if np.isfinite(d) else cd)

        detections.append(BlockDetection(center, box, cd, np.array(corner_depths),
                                         float(area), c))

    detections.sort(key=lambda d: d.area_px, reverse=True)
    return detections, mask


def deproject(u, v, z, K):
    """Pixel (u, v) + depth z → 3D point in the camera optical frame (x right, y down, z forward)."""
    fx, fy, cx, cy = K[0, 0], K[1, 1], K[0, 2], K[1, 2]
    return np.array([(u - cx) * z / fx, (v - cy) * z / fy, z], np.float64)


def detection_points_3d(det, K):
    """Returns (center_3d (3,), corners_3d (4,3)), both in the camera optical frame."""
    center = deproject(det.center_px[0], det.center_px[1], det.center_depth, K)
    corners = np.array([deproject(p[0], p[1], d, K)
                        for p, d in zip(det.corners_px, det.corner_depths)])
    return center, corners


def draw_detection(bgr, det, closing_side=None, text=None):
    """Draw a detection. closing_side: 0 = along corners 0→1, 1 = along corners 1→2
    (gripper closing direction)."""
    out = bgr.copy()
    box = det.corners_px.astype(np.int32)
    cv2.polylines(out, [box], True, (0, 255, 0), 2)
    c = det.center_px
    cv2.circle(out, (int(c[0]), int(c[1])), 4, (0, 0, 255), -1)
    if closing_side is not None:
        a, b = (0, 1) if closing_side == 0 else (1, 2)
        d = det.corners_px[b] - det.corners_px[a]
        p0 = (c - 0.7 * d).astype(int)
        p1 = (c + 0.7 * d).astype(int)
        cv2.arrowedLine(out, tuple(p0), tuple(p1), (255, 0, 255), 2, tipLength=0.15)
        cv2.arrowedLine(out, tuple(p1), tuple(p0), (255, 0, 255), 2, tipLength=0.15)
    if text:
        cv2.putText(out, text, (10, 25), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255, 255, 255), 2)
    return out
