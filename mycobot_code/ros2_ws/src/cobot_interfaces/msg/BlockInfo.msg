# One block as seen by the arm, already converted to the arm base frame (base_link).
# Returned by the /arm/locate_blocks service.

string color                    # lower-case colour name ("red", "blue", ...)
float32 confidence              # 0.0 ~ 1.0, from the vision node
bool graspable                  # vision says pick it, confidence is high enough, and it fits the gripper

geometry_msgs/Point position    # centre of the block's TOP face in base_link [m]
float64 grasp_yaw               # finger closing direction in the base XY plane [rad] (0 if no corners)
float64 width                   # block width across the fingers [m] (0 if no corners)
