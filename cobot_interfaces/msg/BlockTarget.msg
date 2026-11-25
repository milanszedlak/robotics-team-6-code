# One block detected by the camera (published by the vision node, consumed by the arm node)
#
# Frame:     header.frame_id must be the camera optical frame, e.g. camera_color_optical_frame
#            (x right, y down, z forward; units: metres)
# Timestamp: header.stamp must be the capture time of the RGB image
#            (copy header.stamp from the colour image)

std_msgs/Header header

string color                    # lower-case colour name: "red" / "blue" / "green" / "yellow" ... (matches the basket colour)
bool should_grasp               # vision node decides whether this block should be picked
float32 confidence              # 0.0 ~ 1.0

geometry_msgs/Point center      # centre of the block's TOP face [m]
geometry_msgs/Point[4] corners  # the 4 corners of the top-face rotated bounding box [m], in order
                                # (the order returned by cv2.boxPoints is fine)
                                # If unavailable, set all 4 to zero; legacy NaNs are also treated as missing by the arm
