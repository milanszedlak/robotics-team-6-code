# All blocks detected in one image. Publish it even when no block is seen (empty `blocks`).
# The header matches the RGB image (stamp = capture time, frame_id = camera optical frame)
std_msgs/Header header
cobot_interfaces/BlockTarget[] blocks
