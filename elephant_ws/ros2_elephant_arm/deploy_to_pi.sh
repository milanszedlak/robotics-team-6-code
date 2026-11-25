#!/bin/bash
# Copy this workspace's source to the arm's Pi and build it there.
#   ./deploy_to_pi.sh                 # Pi at 10.42.0.107
#   ./deploy_to_pi.sh 10.42.0.50      # other address
# Asks for the Pi's password once (unless an SSH key is set up).
set -euo pipefail
PI="elephant@${1:-10.42.0.107}"
cd "$(dirname "$0")"

tar --exclude=__pycache__ --exclude=.pytest_cache -czf - src README.md | ssh "$PI" '
  set -e
  mkdir -p ~/ros2_elephant_arm
  tar -xzf - -C ~/ros2_elephant_arm
  cd ~/ros2_elephant_arm
  source /opt/ros/jazzy/setup.bash
  echo "== checking dependencies"
  for p in control_msgs trajectory_msgs robot_state_publisher; do
    ros2 pkg prefix $p >/dev/null 2>&1 && echo "  $p: ok" || echo "  $p: MISSING -> sudo apt install ros-jazzy-${p//_/-}"
  done
  python3 -c "import pymycobot" 2>/dev/null && echo "  pymycobot: ok" || echo "  pymycobot: MISSING -> pip install pymycobot"
  echo "== building"
  colcon build --symlink-install --packages-select mycobot_description mycobot_driver
  echo "== done. Start it with:"
  echo "   source ~/ros2_elephant_arm/install/setup.bash && ros2 launch mycobot_driver driver.launch.py"
'
