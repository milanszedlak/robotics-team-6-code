"""ROS2 Jazzy + RealSense: colour blocks with conservative HSV and ROI.

Keys:
  R - click four corners of the block workspace
  C - clear the workspace ROI
  G - click the centre of a green block to calibrate hue
  Q - quit
"""

import time

import cv2
import numpy as np
import rclpy

from cv_bridge import CvBridge
from geometry_msgs.msg import Point, PointStamped
from rclpy.node import Node
from rclpy.qos import qos_profile_sensor_data
from sensor_msgs.msg import CameraInfo, Image
from cobot_interfaces.msg import BlockTarget, BlockTargetArray


# ============================================================
# USER SETTINGS
# ============================================================

VERSION = 'RGY-publish-top-corners-2026-11-11'

RGB_TOPIC = '/camera/camera/color/image_raw'

DEPTH_TOPIC = '/camera/camera/aligned_depth_to_color/image_raw'

INFO_TOPIC = '/camera/camera/color/camera_info'

OUTPUT_TOPIC = '/detected_object/position'


# Depth range (metres)
MIN_DEPTH_M = 0.20
MAX_DEPTH_M = 1.50

MAX_DEPTH_AGE_S = 0.8
MAX_STAMP_GAP_S = 0.5

# Yellow object's top-face dimensions, measured by the team (metres).
# Other colours/shapes are NOT assumed to share these dimensions.
YELLOW_TOP_LENGTH_M = 0.060
YELLOW_TOP_WIDTH_M = 0.030

# Publish preliminary yellow top-face corners for TF2 / interface testing.
# Do not enable physical grasp until geometry and camera-to-arm TF are validated.
CORNER_RANSAC_TOLERANCE_M = 0.004
CORNER_RANSAC_TRIALS = 35


# Object size and shape filtering
MIN_CONTOUR_AREA = 260

MIN_ROTATED_SIDE = 10

MIN_ROTATED_FILL = 0.35

MAX_ASPECT_RATIO = 9.0


# HSV ranges
# OpenCV: H = 0-179, S = 0-255, V = 0-255
HSV_RANGES = {

    'Red': [
        ((0, 75, 45), (12, 255, 255)),
        ((169, 75, 45), (179, 255, 255))
    ],

    'Green': [
        ((77, 125, 55), (97, 255, 255))
    ],

    'Yellow': [
        ((17, 75, 55), (39, 255, 255))
    ]

}


# Additional colour channel checks
BLUE_MINUS_GREEN = 20
BLUE_MINUS_RED = 35

GREEN_MINUS_RED = 14
TEAL_BLUE_MINUS_RED = 16


# Bounding box colours (BGR)
BGR_BOX_COLORS = {

    'Red': (0, 0, 255),

    'Green': (0, 235, 0),

    'Blue': (255, 85, 0),

    'Yellow': (0, 230, 255)

}


WINDOW = (
    'LeoRover Blocks | '
    'R: ROI  G: sample green  C: clear  Q: quit'
)


# ============================================================
# COLOUR DETECTION
# ============================================================

def make_colour_masks(
    frame,
    hsv,
    roi_mask,
    green_center
):

    h, w = hsv.shape[:2]

    masks = {}

    b, g, r = cv2.split(frame)

    bi = b.astype(np.int16)
    gi = g.astype(np.int16)
    ri = r.astype(np.int16)

    for colour, ranges in HSV_RANGES.items():

        # Green hue calibration
        if colour == 'Green' and green_center is not None:

            ranges = [
                (
                    (max(65, green_center - 10), 125, 55),
                    (min(103, green_center + 10), 255, 255)
                )
            ]

        mask = np.zeros(
            (h, w),
            dtype=np.uint8
        )

        for low, high in ranges:

            mask |= cv2.inRange(
                hsv,
                np.array(low, dtype=np.uint8),
                np.array(high, dtype=np.uint8)
            )

        # Apply workspace ROI
        mask = cv2.bitwise_and(
            mask,
            roi_mask
        )

        # Extra blue filtering
        if colour == 'Blue':

            dominant = (
                (bi - gi >= BLUE_MINUS_GREEN)
                &
                (bi - ri >= BLUE_MINUS_RED)
            )

            mask = cv2.bitwise_and(
                mask,
                dominant.astype(np.uint8) * 255
            )

        # Extra green filtering
        elif colour == 'Green':

            dominant = (
                (gi - ri >= GREEN_MINUS_RED)
                &
                (bi - ri >= TEAL_BLUE_MINUS_RED)
            )

            mask = cv2.bitwise_and(
                mask,
                dominant.astype(np.uint8) * 255
            )

        # Remove small noise
        mask = cv2.morphologyEx(
            mask,
            cv2.MORPH_OPEN,
            np.ones((3, 3), dtype=np.uint8)
        )

        # Fill small gaps
        mask = cv2.morphologyEx(
            mask,
            cv2.MORPH_CLOSE,
            np.ones((5, 5), dtype=np.uint8)
        )

        masks[colour] = mask

    return masks


# ============================================================
# FIND OBJECT REGIONS
# ============================================================

def get_colour_regions(mask):

    contours, _ = cv2.findContours(
        mask,
        cv2.RETR_EXTERNAL,
        cv2.CHAIN_APPROX_SIMPLE
    )

    objects = []

    for cnt in contours:

        area = cv2.contourArea(cnt)

        if area < MIN_CONTOUR_AREA:
            continue

        # Rotated bounding rectangle
        rect = cv2.minAreaRect(cnt)

        side_a, side_b = rect[1]

        shorter = min(side_a, side_b)
        longer = max(side_a, side_b)

        if shorter < MIN_ROTATED_SIDE:
            continue

        if longer / max(shorter, 1) > MAX_ASPECT_RATIO:
            continue

        rotated_area = side_a * side_b

        if area / max(rotated_area, 1) < MIN_ROTATED_FILL:
            continue

        x, y, width, height = cv2.boundingRect(cnt)

        moments = cv2.moments(cnt)

        if moments['m00'] > 0:

            u = int(
                moments['m10'] / moments['m00']
            )

            v = int(
                moments['m01'] / moments['m00']
            )

        else:

            u = x + width // 2
            v = y + height // 2

        objects.append(
            (
                rect,
                (x, y, width, height),
                (u, v)
            )
        )

    return objects


# ============================================================
# ROS 2 NODE
# ============================================================

class Object3DDetector(Node):

    def __init__(self):

        super().__init__('object_3d_detector')

        self.bridge = CvBridge()

        self.rgb_msg = None
        self.depth_msg = None

        self.depth_received = None

        self.rgb_seq = 0
        self.last_processed_rgb_seq = -1

        self.depth_seq = 0
        self.last_depth_decoded_seq = -1

        self.depth_image = None
        self.depth_encoding = None

        self.intrinsics = None

        # ROI
        self.roi_points = []
        self.roi_polygon = None
        self.selecting_roi = False

        # Green calibration
        self.green_sample_requested = False
        self.green_hue_center = None

        self.latest_plain_frame = None

        self.quit_requested = False

        # FPS
        self.last_frame_time = None
        self.fps = 0.0
        self.last_corner_debug_log = 0.0

        # ====================================================
        # ROS 2 Subscribers
        # ====================================================

        self.rgb_sub = self.create_subscription(
            Image,
            RGB_TOPIC,
            self.on_rgb,
            qos_profile_sensor_data
        )

        self.depth_sub = self.create_subscription(
            Image,
            DEPTH_TOPIC,
            self.on_depth,
            qos_profile_sensor_data
        )

        self.info_sub = self.create_subscription(
            CameraInfo,
            INFO_TOPIC,
            self.on_info,
            qos_profile_sensor_data
        )

        # ====================================================
        # ROS 2 Publisher
        # ====================================================

        self.xyz_pub = self.create_publisher(
            PointStamped,
            OUTPUT_TOPIC,
            10
        )

        # Integration-test publisher: real targets added in a later step.
        self.blocks_pub = self.create_publisher(
            BlockTargetArray,
            '/vision/blocks',
            10
        )

        # Process newest RGB image
        self.timer = self.create_timer(
            0.02,
            self.process_frame
        )

        # OpenCV window
        cv2.namedWindow(
            WINDOW,
            cv2.WINDOW_NORMAL
        )

        cv2.setMouseCallback(
            WINDOW,
            self.on_mouse
        )

        self.get_logger().info(
            f'Colour-filter version: {VERSION}'
        )

        self.get_logger().info(
            f'Publishing object XYZ to {OUTPUT_TOPIC}'
        )

    # ========================================================
    # RGB CALLBACK
    # ========================================================

    def on_rgb(self, msg):

        self.rgb_msg = msg

        self.rgb_seq += 1

    # ========================================================
    # DEPTH CALLBACK
    # ========================================================

    def on_depth(self, msg):

        self.depth_msg = msg

        self.depth_received = time.monotonic()

        self.depth_seq += 1

    # ========================================================
    # CAMERA INFO CALLBACK
    # ========================================================

    def on_info(self, msg):

        if msg.k[0] > 0 and msg.k[4] > 0:

            self.intrinsics = (
                msg.k[0],
                msg.k[4],
                msg.k[2],
                msg.k[5]
            )

    # ========================================================
    # MOUSE CALLBACK
    # ========================================================

    def on_mouse(
        self,
        event,
        x,
        y,
        flags,
        userdata
    ):

        if event != cv2.EVENT_LBUTTONDOWN:
            return

        # Green calibration
        if self.green_sample_requested:

            self.green_sample_requested = False

            self.calibrate_green(x, y)

        # ROI selection
        elif self.selecting_roi:

            self.roi_points.append(
                (x, y)
            )

            if len(self.roi_points) == 4:

                self.roi_polygon = np.array(
                    self.roi_points,
                    dtype=np.int32
                )

                self.selecting_roi = False

                self.get_logger().info(
                    'Workspace ROI set'
                )

    # ========================================================
    # GREEN CALIBRATION
    # ========================================================

    def calibrate_green(self, x, y):

        frame = self.latest_plain_frame

        if frame is None:
            return

        h, w = frame.shape[:2]

        x = int(np.clip(x, 0, w - 1))
        y = int(np.clip(y, 0, h - 1))

        patch = frame[
            max(0, y - 6):min(h, y + 7),
            max(0, x - 6):min(w, x + 7)
        ]

        patch_hsv = cv2.cvtColor(
            patch,
            cv2.COLOR_BGR2HSV
        )

        good = patch_hsv[:, :, 1] >= 125

        if np.count_nonzero(good) < 10:

            self.get_logger().warning(
                'Sample not saturated enough'
            )

            return

        center = int(
            np.median(
                patch_hsv[:, :, 0][good]
            )
        )

        if not 65 <= center <= 103:

            self.get_logger().warning(
                f'H={center} does not look green'
            )

            return

        self.green_hue_center = center

        self.get_logger().info(
            f'Green H calibrated to {center}'
        )

    # ========================================================
    # KEYBOARD CONTROLS
    # ========================================================

    def handle_key(self):

        key = cv2.waitKey(1) & 0xFF

        if key in (ord('r'), ord('R')):

            self.roi_points = []
            self.roi_polygon = None

            self.selecting_roi = True
            self.green_sample_requested = False

            self.get_logger().info(
                'Click 4 corners around the blocks'
            )

        elif key in (ord('c'), ord('C')):

            self.roi_points = []
            self.roi_polygon = None

            self.selecting_roi = False

            self.get_logger().info(
                'Workspace ROI cleared'
            )

        elif key in (ord('g'), ord('G')):

            self.green_sample_requested = True
            self.selecting_roi = False

            self.get_logger().info(
                'Click middle of green block'
            )

        elif key in (ord('q'), ord('Q')):

            self.quit_requested = True

    # ========================================================
    # GET RECENT DEPTH
    # ========================================================

    def get_recent_depth(self, rgb, h, w):

        if self.depth_msg is None:
            return None

        if self.depth_received is None:
            return None

        age = time.monotonic() - self.depth_received

        if age > MAX_DEPTH_AGE_S:
            return None

        dmsg = self.depth_msg

        stamp_rgb = (
            rgb.header.stamp.sec
            + rgb.header.stamp.nanosec * 1e-9
        )

        stamp_depth = (
            dmsg.header.stamp.sec
            + dmsg.header.stamp.nanosec * 1e-9
        )

        if stamp_rgb and stamp_depth:

            gap = abs(
                stamp_rgb - stamp_depth
            )

            if gap > MAX_STAMP_GAP_S:
                return None

        # Decode only new depth images
        if self.last_depth_decoded_seq != self.depth_seq:

            self.last_depth_decoded_seq = self.depth_seq

            self.depth_image = None
            self.depth_encoding = None

            if dmsg.encoding in ('16UC1', '32FC1'):

                try:

                    self.depth_image = (
                        self.bridge.imgmsg_to_cv2(
                            dmsg,
                            desired_encoding='passthrough'
                        )
                    )

                    self.depth_encoding = dmsg.encoding

                except Exception as exc:

                    self.get_logger().warning(
                        f'Depth decode failed: {exc}'
                    )

        if self.depth_image is None:
            return None

        if self.depth_image.shape[:2] != (h, w):
            return None

        return self.depth_image

    # ========================================================
    # DEPTH AT OBJECT
    # ========================================================

    def depth_at_object(
        self,
        depth,
        mask,
        bbox,
        centre
    ):

        x, y, bw, bh = bbox

        u, v = centre

        h, w = depth.shape[:2]

        patch = depth[
            max(v - 5, 0):min(v + 6, h),
            max(u - 5, 0):min(u + 6, w)
        ].astype(np.float32)

        if self.depth_encoding == '16UC1':
            patch *= 0.001

        valid = patch[
            np.isfinite(patch)
            & (patch >= MIN_DEPTH_M)
            & (patch <= MAX_DEPTH_M)
        ]

        # Fallback: sample pixels inside object mask
        if len(valid) < 5:

            region = depth[
                y:y + bh:3,
                x:x + bw:3
            ].astype(np.float32)

            region_mask = mask[
                y:y + bh:3,
                x:x + bw:3
            ] > 0

            if self.depth_encoding == '16UC1':
                region *= 0.001

            valid = region[region_mask]

            valid = valid[
                np.isfinite(valid)
                & (valid >= MIN_DEPTH_M)
                & (valid <= MAX_DEPTH_M)
            ]

        if len(valid) < 5:
            return None

        return float(
            np.median(valid)
        )

    # ========================================================
    # EXPERIMENTAL 3D CORNER DIAGNOSTICS (YELLOW RECTANGLE ONLY)
    # ========================================================

    def estimate_yellow_corner_geometry(self, depth, mask, bbox, rect):
        """Estimate yellow top-face corners from depth-plane inliers.

        Unlike the earlier diagnostic, the final image rectangle is fitted to
        the pixels which lie on the recovered 3D plane, NOT to the entire
        colour silhouette (which may also contain side faces).

        Important: this is STILL a diagnostic estimate, not a certified grasp.
        """
        if depth is None or self.intrinsics is None:
            return None

        x, y, bw, bh = bbox
        h, w = depth.shape[:2]
        x0, y0 = max(0, x), max(0, y)
        x1, y1 = min(w, x + bw), min(h, y + bh)
        if x1 - x0 < 15 or y1 - y0 < 15:
            return None

        # Start with the colour mask restricted to this object's rotated box.
        local_box = cv2.boxPoints(rect).astype(np.int32)
        local_box[:, 0] -= x0
        local_box[:, 1] -= y0
        local_mask = np.zeros((y1 - y0, x1 - x0), dtype=np.uint8)
        cv2.fillConvexPoly(local_mask, local_box, 255)
        local_mask = cv2.bitwise_and(local_mask, mask[y0:y1, x0:x1])

        # Interior pixels are preferred for RANSAC: edges have noisy depth.
        interior = cv2.erode(
            local_mask, np.ones((3, 3), np.uint8), iterations=1
        )
        sy, sx = np.nonzero(interior[::3, ::3])
        if len(sx) < 80:
            return None
        us = (x0 + sx * 3).astype(np.float64)
        vs = (y0 + sy * 3).astype(np.float64)
        zs = depth[vs.astype(np.intp), us.astype(np.intp)].astype(np.float64)
        if self.depth_encoding == '16UC1':
            zs *= 0.001

        valid = (np.isfinite(zs) &
                 (zs >= MIN_DEPTH_M) & (zs <= MAX_DEPTH_M))
        us, vs, zs = us[valid], vs[valid], zs[valid]
        if len(zs) < 80:
            return None
        if len(zs) > 1200:
            ind = np.linspace(0, len(zs) - 1, 1200, dtype=np.intp)
            us, vs, zs = us[ind], vs[ind], zs[ind]

        fx, fy, cx, cy = self.intrinsics
        xyz = np.column_stack(((us - cx) * zs / fx,
                               (vs - cy) * zs / fy,
                               zs))

        rng = np.random.default_rng(31415)
        best_inliers = None
        best_count = 0
        for _ in range(CORNER_RANSAC_TRIALS):
            sample_idx = rng.choice(len(xyz), 3, replace=False)
            p0, p1, p2 = xyz[sample_idx]
            normal = np.cross(p1 - p0, p2 - p0)
            magnitude = np.linalg.norm(normal)
            if magnitude < 1e-9:
                continue
            normal /= magnitude
            residuals = np.abs((xyz - p0) @ normal)
            inliers = residuals < CORNER_RANSAC_TOLERANCE_M
            count = int(np.count_nonzero(inliers))
            if count > best_count:
                best_inliers = inliers
                best_count = count

        if best_inliers is None or best_count < max(50, len(xyz) * 0.40):
            return None

        plane_points = xyz[best_inliers]
        centroid = np.mean(plane_points, axis=0)
        _, _, vh = np.linalg.svd(plane_points - centroid, full_matrices=False)
        normal = vh[-1]
        d = -float(np.dot(normal, centroid))
        fit_rms = float(np.sqrt(np.mean(
            np.square((plane_points @ normal) + d)
        )))

        # Important improvement: classify ALL colour-mask depth pixels
        # against the recovered 3D plane, not only the 1/3 subsample.
        ly, lx = np.nonzero(local_mask)
        if len(lx) < 80:
            return None
        full_us = (x0 + lx).astype(np.float64)
        full_vs = (y0 + ly).astype(np.float64)
        full_zs = depth[full_vs.astype(np.intp),
                        full_us.astype(np.intp)].astype(np.float64)
        if self.depth_encoding == '16UC1':
            full_zs *= 0.001
        full_valid = (np.isfinite(full_zs) &
                      (full_zs >= MIN_DEPTH_M) &
                      (full_zs <= MAX_DEPTH_M))
        full_xyz = np.column_stack((
            (full_us - cx) * full_zs / fx,
            (full_vs - cy) * full_zs / fy,
            full_zs
        ))
        full_residuals = np.abs(full_xyz @ normal + d)
        on_plane = full_valid & (
            full_residuals < CORNER_RANSAC_TOLERANCE_M
        )
        if int(np.count_nonzero(on_plane)) < 80:
            return None

        plane_mask = np.zeros_like(local_mask, dtype=np.uint8)
        plane_mask[ly[on_plane], lx[on_plane]] = 255
        plane_mask = cv2.morphologyEx(
            plane_mask, cv2.MORPH_CLOSE, np.ones((3, 3), np.uint8)
        )
        planar_contours, _ = cv2.findContours(
            plane_mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE
        )
        if not planar_contours:
            return None
        largest = max(planar_contours, key=cv2.contourArea)
        if cv2.contourArea(largest) < 100:
            return None

        # Rectangle of the plane-supported top-face silhouette.
        # Still approximate, especially for occluded/bevelled edges.
        plane_rect = cv2.minAreaRect(largest)
        planar_pixels = cv2.boxPoints(plane_rect).astype(np.float64)
        planar_pixels[:, 0] += x0
        planar_pixels[:, 1] += y0

        rays = np.column_stack((
            (planar_pixels[:, 0] - cx) / fx,
            (planar_pixels[:, 1] - cy) / fy,
            np.ones(4)
        ))
        denom = rays @ normal
        if np.any(np.abs(denom) < 1e-5):
            return None
        depths = -d / denom
        if np.any(~np.isfinite(depths)) or np.any(
            (depths < MIN_DEPTH_M) | (depths > MAX_DEPTH_M)
        ):
            return None
        corners_xyz = rays * depths[:, None]

        edges = np.linalg.norm(
            np.roll(corners_xyz, -1, axis=0) - corners_xyz, axis=1
        )
        opposite_means = (
            (edges[0] + edges[2]) / 2,
            (edges[1] + edges[3]) / 2
        )
        length_m, width_m = sorted(opposite_means, reverse=True)
        support = best_count / len(xyz)
        plausible = (
            support >= 0.60 and fit_rms < 0.004 and
            0.75 <= length_m / YELLOW_TOP_LENGTH_M <= 1.25 and
            0.75 <= width_m / YELLOW_TOP_WIDTH_M <= 1.25
        )
        return {
            'corners_xyz': corners_xyz,
            'corner_pixels': planar_pixels,
            'length_m': float(length_m),
            'width_m': float(width_m),
            'support': float(support),
            'rms_m': fit_rms,
            'plausible': bool(plausible),
        }

    # ========================================================
    # DRAW TEXT
    # ========================================================

    @staticmethod
    def draw_text(
        frame,
        text,
        pos,
        color,
        scale=0.46
    ):

        cv2.putText(
            frame,
            text,
            pos,
            cv2.FONT_HERSHEY_SIMPLEX,
            scale,
            (0, 0, 0),
            3,
            cv2.LINE_AA
        )

        cv2.putText(
            frame,
            text,
            pos,
            cv2.FONT_HERSHEY_SIMPLEX,
            scale,
            color,
            1,
            cv2.LINE_AA
        )

    # ========================================================
    # PROCESS RGB IMAGE
    # ========================================================

    def process_frame(self):

        if self.rgb_msg is None:

            self.handle_key()
            return

        if self.rgb_seq == self.last_processed_rgb_seq:

            self.handle_key()
            return

        msg = self.rgb_msg

        self.last_processed_rgb_seq = self.rgb_seq

        try:

            frame = self.bridge.imgmsg_to_cv2(
                msg,
                desired_encoding='bgr8'
            ).copy()

        except Exception as exc:

            self.get_logger().warning(
                f'RGB decode failed: {exc}'
            )

            return

        self.latest_plain_frame = frame.copy()

        h, w = frame.shape[:2]

        hsv = cv2.cvtColor(
            frame,
            cv2.COLOR_BGR2HSV
        )

        # ====================================================
        # ROI MASK
        # ====================================================

        roi_mask = np.full(
            (h, w),
            255,
            dtype=np.uint8
        )

        if self.roi_polygon is not None:

            roi_mask.fill(0)

            cv2.fillPoly(
                roi_mask,
                [self.roi_polygon],
                255
            )

        # ====================================================
        # COLOUR MASKS
        # ====================================================

        masks = make_colour_masks(
            frame,
            hsv,
            roi_mask,
            self.green_hue_center
        )

        depth = self.get_recent_depth(
            msg,
            h,
            w
        )

        counts = {
            name: 0
            for name in HSV_RANGES
        }

        # One batch per RGB frame; use the original image timestamp and frame.
        blocks_msg = BlockTargetArray()
        blocks_msg.header = msg.header

        # ====================================================
        # PROCESS ALL COLOURS
        # ====================================================

        for colour, mask in masks.items():

            regions = get_colour_regions(mask)

            for rect, bbox, centre in regions:

                counts[colour] += 1

                u, v = centre

                x, y, bw, bh = bbox

                color_bgr = BGR_BOX_COLORS[colour]

                coords = 'XYZ: --'
                block = None  # Corresponding array entry, if depth is valid.

                # ============================================
                # XYZ CALCULATION
                # ============================================

                if (
                    depth is not None
                    and self.intrinsics is not None
                ):

                    z = self.depth_at_object(
                        depth,
                        mask,
                        bbox,
                        centre
                    )

                    if z is not None:

                        fx, fy, cx, cy = self.intrinsics

                        X = (u - cx) * z / fx

                        Y = (v - cy) * z / fy

                        # ROS 2 Publisher
                        point = PointStamped()

                        point.header = msg.header

                        point.point.x = float(X)
                        point.point.y = float(Y)
                        point.point.z = float(z)

                        self.xyz_pub.publish(point)

                        # Publish a 3D detection candidate for the arm team.
                        # The point is an estimate on the visible object surface,
                        # NOT a validated top-face centre or complete grasp pose.
                        block = BlockTarget()
                        block.header = msg.header
                        block.color = colour.lower()
                        block.should_grasp = False  # Interface test only: no arm motion.
                        block.confidence = 0.0      # HSV detector has no calibrated confidence.
                        block.center = Point(x=float(X), y=float(Y), z=float(z))

                        # NaN means "not measured"; never fabricate corners.
                        block.corners = [
                            Point(x=float('nan'), y=float('nan'), z=float('nan'))
                            for _ in range(4)
                        ]
                        blocks_msg.blocks.append(block)

                        coords = (
                            f'X:{X:+.2f} '
                            f'Y:{Y:+.2f} '
                            f'Z:{z:.2f}m'
                        )

                # ============================================
                # YELLOW 3D CORNER DIAGNOSTICS ONLY
                # ============================================
                # Debug three-dimensional geometry without changing the
                # published /vision/blocks message or grasp eligibility.
                if colour == 'Yellow':
                    geometry = self.estimate_yellow_corner_geometry(
                        depth, mask, bbox, rect
                    )
                    if geometry is None:
                        corner_status = '3D corners: no reliable plane'
                    else:
                        corner_status = (
                            f'3D: L={geometry["length_m"]*100:.1f}cm '
                            f'W={geometry["width_m"]*100:.1f}cm '
                            f'fit={geometry["support"]:.2f} '
                            f'{"PRECHECK" if geometry["plausible"] else "UNVERIFIED"}'
                        )

                        # Publish the *estimated* 3D top corners only when
                        # the plane and dimensions pass preliminary checks.
                        # Do not invent corners for other shapes/colours.
                        if geometry['plausible'] and block is not None:
                            top_xyz = np.asarray(
                                geometry['corners_xyz'], dtype=np.float64
                            )
                            if (top_xyz.shape == (4, 3) and
                                    np.all(np.isfinite(top_xyz))):
                                # Preserve the same adjacent, cyclic corner
                                # order used for T1..T4 in the display.
                                block.corners = [
                                    Point(x=float(x3), y=float(y3), z=float(z3))
                                    for x3, y3, z3 in top_xyz
                                ]

                                # For yellow, the API now reports an
                                # *estimated top-face centre*, not the raw
                                # colour-mask centroid depth sample.
                                top_c = np.mean(top_xyz, axis=0)
                                block.center = Point(
                                    x=float(top_c[0]),
                                    y=float(top_c[1]),
                                    z=float(top_c[2])
                                )
                                # Keep False: interface/TF tests only.
                                block.should_grasp = False

                    # Throttle logs instead of printing at video frame rate.
                    if time.monotonic() - self.last_corner_debug_log >= 2.0:
                        self.get_logger().info(corner_status)
                        self.last_corner_debug_log = time.monotonic()

                # ============================================
                # DRAW ROTATED BOUNDING BOX
                # ============================================

                points = cv2.boxPoints(
                    rect
                ).astype(np.int32)

                cv2.polylines(
                    frame,
                    [points],
                    True,
                    color_bgr,
                    2
                )

                # ============================================
                # DEBUG: YELLOW OBJECT 2D BOUNDING-BOX CORNERS
                # These are image pixels, NOT verified 3D
                # corners of the physical object's top face.
                # ============================================
                if colour == 'Yellow':
                    for i, (px, py) in enumerate(points):
                        px = int(px)
                        py = int(py)

                        cv2.circle(
                            frame,
                            (px, py),
                            5,
                            (255, 0, 255),
                            -1
                        )

                        cv2.putText(
                            frame,
                            f'P{i + 1}',
                            (max(0, min(w - 30, px + 6)),
                             max(16, min(h - 6, py - 6))),
                            cv2.FONT_HERSHEY_SIMPLEX,
                            0.5,
                            (255, 0, 255),
                            2,
                            cv2.LINE_AA
                        )

                # Cyan T1..T4 = estimated top-plane corners.
                # Magenta P1..P4 = original full-colour bounding box.
                # Estimated corners are published only for yellow when
                # geometry checks pass. Grasp is still prohibited.
                if colour == 'Yellow' and geometry is not None:
                    top_pixels = np.rint(
                        geometry['corner_pixels']
                    ).astype(np.int32)
                    cv2.polylines(
                        frame, [top_pixels], True, (255, 255, 0), 2
                    )
                    for i, (px, py) in enumerate(top_pixels):
                        px, py = int(px), int(py)
                        cv2.circle(frame, (px, py), 4, (255, 255, 0), -1)
                        cv2.putText(
                            frame, f'T{i + 1}',
                            (max(0, min(w - 32, px - 23)),
                             max(14, min(h - 5, py + 17))),
                            cv2.FONT_HERSHEY_SIMPLEX, 0.42,
                            (255, 255, 0), 1, cv2.LINE_AA
                        )

                if colour == 'Yellow':
                    # Diagnostic overlay; numerical corners are available
                    # on /vision/blocks when preliminary checks pass.
                    self.draw_text(
                        frame,
                        corner_status,
                        (max(4, x), min(h - 5, y + bh + 31)),
                        (255, 0, 255),
                        0.37
                    )

                cv2.circle(
                    frame,
                    (u, v),
                    4,
                    (255, 255, 255),
                    -1
                )

                tx = min(
                    max(4, x),
                    max(4, w - 170)
                )

                self.draw_text(
                    frame,
                    f'{colour} {counts[colour]}',
                    (tx, max(67, y - 6)),
                    color_bgr,
                    0.48
                )

                self.draw_text(
                    frame,
                    coords,
                    (tx, min(h - 9, y + bh + 15)),
                    color_bgr,
                    0.38
                )

        # ====================================================
        # DRAW ROI
        # ====================================================

        if self.roi_polygon is not None:

            cv2.polylines(
                frame,
                [self.roi_polygon],
                True,
                (0, 255, 255),
                2
            )

        elif self.selecting_roi and self.roi_points:

            for p in self.roi_points:

                cv2.circle(
                    frame,
                    p,
                    5,
                    (0, 255, 255),
                    -1
                )

            if len(self.roi_points) >= 2:

                cv2.polylines(
                    frame,
                    [
                        np.array(
                            self.roi_points,
                            dtype=np.int32
                        )
                    ],
                    False,
                    (0, 255, 255),
                    2
                )

        # ====================================================
        # FPS
        # ====================================================

        now = time.monotonic()

        if self.last_frame_time is not None:

            delta = now - self.last_frame_time

            if delta > 0:

                measured_fps = 1.0 / delta

                if self.fps == 0:

                    self.fps = measured_fps

                else:

                    self.fps = (
                        0.75 * self.fps
                        + 0.25 * measured_fps
                    )

        self.last_frame_time = now

        # ====================================================
        # DISPLAY INFORMATION
        # ====================================================

        cv2.rectangle(
            frame,
            (0, 0),
            (w, 54),
            (0, 0, 0),
            -1
        )

        self.draw_text(
            frame,
            (
                f'{VERSION}  '
                f'RGB: {self.fps:.1f} FPS'
            ),
            (8, 21),
            (255, 255, 255),
            0.49
        )

        total = sum(
            counts.values()
        )

        if self.roi_polygon is not None:

            status = 'ROI ON'

        else:

            status = 'ROI OFF (R to select)'

        self.draw_text(
            frame,
            (
                f'Objects:{total}  '
                f'R:{counts["Red"]} '
                f'G:{counts["Green"]} '
                f'Y:{counts["Yellow"]} | '
                f'{status}'
            ),
            (8, 43),
            (255, 255, 255),
            0.46
        )

        if self.green_sample_requested:

            self.draw_text(
                frame,
                'Click CENTER of green block',
                (10, h - 17),
                (0, 255, 255),
                0.55
            )

        elif self.selecting_roi:

            self.draw_text(
                frame,
                (
                    'ROI: click 4 corners '
                    f'({len(self.roi_points)}/4)'
                ),
                (10, h - 17),
                (0, 255, 255),
                0.55
            )

        # Publish valid-depth candidates for this RGB frame.
        # If nothing has valid depth, send blocks: [].
        # All should_grasp fields remain False pending physical validation.
        self.blocks_pub.publish(blocks_msg)

        cv2.imshow(
            WINDOW,
            frame
        )

        self.handle_key()


# ============================================================
# MAIN
# ============================================================

def main():

    rclpy.init()

    node = Object3DDetector()

    try:

        while rclpy.ok() and not node.quit_requested:

            rclpy.spin_once(
                node,
                timeout_sec=0.01
            )

    except KeyboardInterrupt:

        pass

    finally:

        node.destroy_node()

        cv2.destroyAllWindows()

        if rclpy.ok():

            rclpy.shutdown()


if __name__ == '__main__':

    main()
