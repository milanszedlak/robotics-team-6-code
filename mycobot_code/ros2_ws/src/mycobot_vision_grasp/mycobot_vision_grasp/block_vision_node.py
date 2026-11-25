"""Block vision node: finds coloured blocks in the depth camera image and publishes their 3D pose.

Works with the real RealSense D435 (realsense2_camera, 16UC1 depth in millimetres) and with the
Gazebo camera (32FC1 depth in metres); the topic names are the same. Runs on the laptop / NUC.

  Subscribes: /camera/camera/color/image_raw
              /camera/camera/aligned_depth_to_color/image_raw   (realsense: align_depth.enable:=true)
              /camera/camera/color/camera_info
  Publishes:  /vision/blocks (cobot_interfaces/BlockTargetArray), at most `process_rate` Hz
              /vision/debug_image (sensor_msgs/Image): detections drawn on the colour image

The detection itself is in block_detector.py (HSV threshold → minAreaRect → depth → 3D).
HSV ranges per colour are parameters `hsv.<colour>`: [h,s,v low, h,s,v high, (second range...)].
"""
import cv2
import message_filters
import numpy as np
import rclpy
from cobot_interfaces.msg import BlockTarget, BlockTargetArray
from cv_bridge import CvBridge
from geometry_msgs.msg import Point
from rclpy.node import Node
from rclpy.qos import qos_profile_sensor_data
from rclpy.time import Time
from sensor_msgs.msg import CameraInfo, Image

from .block_detector import detect_blocks, detection_points_3d, draw_detection

DEFAULT_HSV = {
    'red': [0, 120, 70, 10, 255, 255, 170, 120, 70, 180, 255, 255],
    'blue': [100, 120, 50, 130, 255, 255],
    'green': [40, 80, 50, 85, 255, 255],
    'yellow': [20, 100, 100, 35, 255, 255],
}


class BlockVisionNode(Node):

    def __init__(self):
        super().__init__('block_vision')
        P = self.declare_parameter
        color_topic = P('color_topic', '/camera/camera/color/image_raw').value
        depth_topic = P('depth_topic', '/camera/camera/aligned_depth_to_color/image_raw').value
        info_topic = P('camera_info_topic', '/camera/camera/color/camera_info').value
        self.colors = list(P('colors', ['red', 'blue', 'green']).value)
        self.grasp_colors = list(P('grasp_colors', ['red', 'blue', 'green']).value)
        self.max_width = P('gripper_max_opening', 0.045).value
        self.min_area = P('min_area', 300.0).value
        self.min_fill = P('min_fill_ratio', 0.75).value
        self.depth_min = P('depth_min', 0.07).value
        self.depth_max = P('depth_max', 2.0).value
        rate = P('process_rate', 10.0).value       # 0 = process every frame
        self.min_period = 1.0 / rate if rate > 0 else 0.0
        self.hsv = {}
        for c in self.colors:
            v = list(P(f'hsv.{c}', DEFAULT_HSV.get(c, [0, 0, 0, 0, 0, 0])).value)
            self.hsv[c] = [(v[i:i + 3], v[i + 3:i + 6]) for i in range(0, len(v), 6)]

        self.bridge = CvBridge()
        self.K = None
        self._last = None
        self.create_subscription(CameraInfo, info_topic, self._on_info, qos_profile_sensor_data)
        subs = [message_filters.Subscriber(self, Image, t, qos_profile=qos_profile_sensor_data)
                for t in (color_topic, depth_topic)]
        self.sync = message_filters.ApproximateTimeSynchronizer(subs, 10, 0.05)
        self.sync.registerCallback(self._on_images)
        self.pub = self.create_publisher(BlockTargetArray, '/vision/blocks', 10)
        self.debug_pub = self.create_publisher(Image, '/vision/debug_image', 1)
        self.get_logger().info(f'Looking for {self.colors} blocks on {color_topic}')

    def _on_info(self, msg):
        self.K = np.array(msg.k, np.float64).reshape(3, 3)

    def _on_images(self, color_msg, depth_msg):
        if self.K is None:
            self.get_logger().warn('No camera_info yet', throttle_duration_sec=5.0)
            return
        stamp = Time.from_msg(color_msg.header.stamp)
        if self._last is not None and (stamp - self._last).nanoseconds * 1e-9 < self.min_period:
            return
        self._last = stamp
        color = self.bridge.imgmsg_to_cv2(color_msg, 'bgr8')
        depth = self.bridge.imgmsg_to_cv2(depth_msg, 'passthrough')

        out = BlockTargetArray()
        out.header = color_msg.header            # ★ stamp = RGB capture time; frame = optical frame
        debug = color.copy()
        for name in self.colors:
            dets, _ = detect_blocks(color, depth, self.hsv[name], self.min_area,
                                    depth_range=(self.depth_min, self.depth_max))
            for det in dets:
                center, corners = detection_points_3d(det, self.K)
                rect_area = (np.linalg.norm(det.corners_px[1] - det.corners_px[0]) *
                             np.linalg.norm(det.corners_px[2] - det.corners_px[1]))
                fill = float(det.area_px / rect_area) if rect_area > 0 else 0.0
                width = min(np.linalg.norm(corners[1] - corners[0]),
                            np.linalg.norm(corners[2] - corners[1]))

                b = BlockTarget()
                b.header = color_msg.header
                b.color = name
                b.confidence = float(min(1.0, fill))
                b.should_grasp = bool(name in self.grasp_colors and fill >= self.min_fill
                                      and width <= self.max_width)
                b.center = Point(x=float(center[0]), y=float(center[1]), z=float(center[2]))
                b.corners = [Point(x=float(p[0]), y=float(p[1]), z=float(p[2])) for p in corners]
                out.blocks.append(b)
                debug = draw_detection(debug, det)
                u, v = det.center_px.astype(int)
                cv2.putText(debug, f'{name} {width * 100:.1f}cm {"GRASP" if b.should_grasp else "skip"}',
                            (u - 40, v - 12), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 2)
        self.pub.publish(out)
        if self.debug_pub.get_subscription_count() > 0:
            dm = self.bridge.cv2_to_imgmsg(debug, 'bgr8')
            dm.header = color_msg.header
            self.debug_pub.publish(dm)


def main():
    rclpy.init()
    node = BlockVisionNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.try_shutdown()


if __name__ == '__main__':
    main()
