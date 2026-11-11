# 🤖 Team 6 - Leo Rover Codebase

Welcome to the main software repository for Team 6's Leo Rover. This repository contains all ROS/ROS2 packages, control scripts, autonomous navigation nodes, and custom hardware interface code.

# Virtual RPLIDAR Simulation on Leo Rover (ROS 2 Jazzy + Gazebo)

This guide explains how to add a virtual 2D LiDAR sensor to the Leo Rover simulation, publish LiDAR data through ROS 2, and visualise the laser scan in RViz2.

The simulation uses:
- **Ubuntu:** 24.04
- **ROS 2:** Jazzy
- **Simulator:** Gazebo Harmonic
- **Robot:** Leo Rover
- **Virtual sensor:** 2D GPU LiDAR
- **ROS message:** `sensor_msgs/msg/LaserScan`

---

## 1. Prerequisites

### 1.1 System Requirements

Make sure you have:

| Software | Required Version |
|---|---|
| Ubuntu | 24.04 |
| ROS 2 | Jazzy |
| Gazebo | Harmonic |

### 1.2 Required ROS 2 Packages

The following packages are required for this project:

| Package | Purpose |
|---|---|
| `leo_gz_bringup` | Launches the Leo Rover simulation in Gazebo |
| `leo_description` | Provides the Leo Rover robot description (URDF/Xacro) |
| `ros_gz_bridge` | Bridges Gazebo sensor data to ROS 2 topics |
| `rviz2` | Visualises LiDAR data |
| `xacro` | Processes the robot's Xacro description |
| `tf2_ros` | Provides TF transformation tools |
| `tf2_tools` | Provides tools for inspecting TF frames |

### 1.3 Install Missing Packages

First, update the package lists:

```bash
sudo apt update
```

Install the packages individually if they are missing:

**RViz2**
```bash
sudo apt install ros-jazzy-rviz2
```

**ROS-Gazebo Bridge**
```bash
sudo apt install ros-jazzy-ros-gz-bridge
```

**Xacro**
```bash
sudo apt install ros-jazzy-xacro
```

**TF2 ROS**
```bash
sudo apt install ros-jazzy-tf2-ros
```

**TF2 Tools**
```bash
sudo apt install ros-jazzy-tf2-tools
```

### 1.4 Check Installed Packages

You can check whether the required ROS 2 packages are available:

```bash
ros2 pkg list | grep -E 'leo_gz_bringup|leo_description|ros_gz_bridge|rviz2|xacro|tf2_ros|tf2_tools'
```

If a package does not appear, install the corresponding package or follow the Leo Rover installation instructions.

**Note:** `leo_gz_bringup` and `leo_description` are provided by the Leo Rover simulation installation. Make sure the Leo Rover simulation packages are installed before proceeding.

---

## 2. Create a Workspace

Create a workspace for the modified Leo Rover description package:

```bash
mkdir -p ~/lidar_sim/src
cd ~/lidar_sim/src
```

Copy the original Leo Rover description package into the workspace:

```bash
cp -r /opt/ros/jazzy/share/leo_description .
```

Navigate into the package:

```bash
cd ~/lidar_sim/src/leo_description
```

---

## 3. Configure the Package

Create or edit `CMakeLists.txt` in:

```text
~/lidar_sim/src/leo_description/CMakeLists.txt
```

Use the following content:

```cmake
cmake_minimum_required(VERSION 3.8)
project(leo_description)

find_package(ament_cmake REQUIRED)

install(
  DIRECTORY urdf launch models
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
```

This allows the modified URDF, launch files and robot models to be installed into the workspace.

---

## 4. Add the Virtual LiDAR to the Robot

Open:

```text
~/lidar_sim/src/leo_description/urdf/macros.xacro
```

### 4.1 Add the LiDAR Link and Joint

Inside the `leo_sim` macro, immediately after the `<xacro:leo .../>` element, add:

```xml
<!-- Virtual LiDAR -->
<link name="${link_prefix}laser_link">
  <inertial>
    <mass value="0.01"/>
    <origin xyz="0 0 0"/>
    <inertia ixx="0.00001" ixy="0" ixz="0"
             iyy="0.00001" iyz="0"
             izz="0.00001"/>
  </inertial>
</link>

<joint name="${link_prefix}laser_joint" type="fixed">
  <parent link="${link_prefix}base_link"/>
  <child link="${link_prefix}laser_link"/>
  <origin xyz="0 0 0.20" rpy="0 0 0"/>
</joint>
```

This attaches the virtual LiDAR 20 cm above the robot's `base_link`.

### 4.2 Add the LiDAR Sensor

Inside the `leo_gazebo` macro, before its closing `</xacro:macro>`, add:

```xml
<!-- Virtual 2D LiDAR -->
<gazebo reference="${link_prefix}laser_link">
  <sensor name="leo_lidar" type="gpu_lidar">
    <always_on>true</always_on>
    <update_rate>10</update_rate>
    <visualize>true</visualize>
    <topic>/scan</topic>
    <gz_frame_id>${link_prefix}laser_link</gz_frame_id>

    <lidar>
      <scan>
        <horizontal>
          <samples>360</samples>
          <resolution>1</resolution>
          <min_angle>-3.14159</min_angle>
          <max_angle>3.14159</max_angle>
        </horizontal>
      </scan>

      <range>
        <min>0.15</min>
        <max>16.0</max>
        <resolution>0.01</resolution>
      </range>
    </lidar>
  </sensor>
</gazebo>
```

### 4.3 LiDAR Configuration

| Parameter | Value | Description |
|---|---:|---|
| Sensor type | `gpu_lidar` | Gazebo GPU LiDAR sensor |
| Update rate | 10 Hz | 10 scans per second |
| Samples | 360 | Number of horizontal samples |
| Field of view | 360° | Full horizontal scan |
| Minimum range | 0.15 m | Minimum detection distance |
| Maximum range | 16.0 m | Maximum detection distance |
| Range resolution | 0.01 m | Range measurement resolution |
| Frame ID | `laser_link` | LiDAR coordinate frame |
| ROS topic | `/scan` | Published laser scan topic |

---

## 5. Build the Workspace

Return to the workspace root:

```bash
cd ~/lidar_sim
```

Build the package:

```bash
colcon build --symlink-install
```

Source the ROS 2 environment and the workspace overlay:

```bash
source /opt/ros/jazzy/setup.bash
source ~/lidar_sim/install/setup.bash
```

You can verify that the modified package is being used:

```bash
ros2 pkg prefix leo_description
```

The expected path is:

```text
/home/<your_username>/lidar_sim/install/leo_description
```

---

## 6. Launch Gazebo

Open **Terminal 1**.

Source the environments:

```bash
source /opt/ros/jazzy/setup.bash
source ~/lidar_sim/install/setup.bash
```

Launch the Leo Rover simulation:

```bash
ros2 launch leo_gz_bringup leo_gz.launch.py
```

Wait for the Leo Rover to appear in Gazebo.

**Important:** Press the Play button in Gazebo if the simulation is paused.

---

## 7. Start the ROS-Gazebo Bridge

Gazebo publishes its sensor data using Gazebo Transport messages. The bridge converts these messages into ROS 2 messages.

Open **Terminal 2**:

```bash
source /opt/ros/jazzy/setup.bash
source ~/lidar_sim/install/setup.bash
```

Start the bridge:

```bash
ros2 run ros_gz_bridge parameter_bridge /scan@sensor_msgs/msg/LaserScan[gz.msgs.LaserScan
```

This bridges the Gazebo LiDAR data to the ROS 2 `/scan` topic.

---

## 8. Check the LiDAR Data

Open **Terminal 3**:

```bash
source /opt/ros/jazzy/setup.bash
```

Check whether the topic exists:

```bash
ros2 topic list
```

You should see:

```text
/scan
```

Check the message type:

```bash
ros2 topic info /scan
```

Expected message type:

```text
sensor_msgs/msg/LaserScan
```

Check whether the sensor is publishing data:

```bash
ros2 topic hz /scan
```

The expected publishing rate is approximately 10 Hz.

To inspect one scan:

```bash
ros2 topic echo /scan --once
```

The output contains angle information, range limits and an array of distance measurements.

---

## 9. Visualise the LiDAR in RViz2

Open **Terminal 4**:

```bash
source /opt/ros/jazzy/setup.bash
source ~/lidar_sim/install/setup.bash
rviz2
```

Configure RViz2:

### 9.1 Set the Fixed Frame

In the left-hand panel:

1. Expand **Global Options**.
2. Find **Fixed Frame**.
3. Change it to:

```text
laser_link
```

### 9.2 Add a LaserScan Display

1. Click **Add** in the bottom-left corner.
2. Select **By display type**.
3. Choose **LaserScan**.
4. Click **OK**.

### 9.3 Configure the LaserScan Display

In the LaserScan settings:

| Setting | Value |
|---|---|
| Topic | `/scan` |
| Reliability Policy | Best Effort (if required) |
| Size (m) | `0.03` |

You should now see coloured LiDAR points in RViz2.

---

## 10. Test the Virtual LiDAR

To verify that the sensor is working:

1. Add a box or another obstacle in Gazebo.
2. Observe the LiDAR points in RViz2.
3. Move the Leo Rover forward.
4. Observe how the scan changes.
5. Rotate the Leo Rover.
6. Observe how the detected obstacle positions change.

The LiDAR measures distances relative to its own coordinate frame.

When the robot moves or rotates, the LiDAR's position and orientation change, so the scan measurements change accordingly.

---

## 11. Understand the TF Relationship

The LiDAR is attached to the robot using a fixed joint.

The relationship is:

```text
base_link
    |
    |  Fixed Joint
    |  Translation: (0, 0, 0.20 m)
    |
laser_link
```

To inspect the transform, run:

```bash
ros2 run tf2_ros tf2_echo base_link laser_link
```

Expected translation:

```text
Translation: [0.000, 0.000, 0.200]
```

Expected rotation:

```text
Roll:  0 degrees
Pitch: 0 degrees
Yaw:   0 degrees
```

This confirms that the LiDAR is mounted 20 cm above the robot's base frame, with the same orientation.

---

## 12. Starting the Simulation Again

Once the workspace has been built, you do not need to rebuild it every time.

Open four terminals and run the following commands.

**Terminal 1 – Gazebo:**

```bash
source /opt/ros/jazzy/setup.bash
source ~/lidar_sim/install/setup.bash
ros2 launch leo_gz_bringup leo_gz.launch.py
```

**Terminal 2 – ROS-Gazebo Bridge:**

```bash
source /opt/ros/jazzy/setup.bash
source ~/lidar_sim/install/setup.bash
ros2 run ros_gz_bridge parameter_bridge /scan@sensor_msgs/msg/LaserScan[gz.msgs.LaserScan
```

**Terminal 3 – RViz2:**

```bash
source /opt/ros/jazzy/setup.bash
source ~/lidar_sim/install/setup.bash
rviz2
```

**Terminal 4 – Optional LiDAR monitoring:**

```bash
source /opt/ros/jazzy/setup.bash
ros2 topic hz /scan
```

Remember to press Play in Gazebo if the simulation is paused.

---

## 13. Expected Result

After completing the guide, you should have:

- A Leo Rover running in Gazebo.
- A virtual 360° LiDAR attached to the robot.
- LiDAR data published on `/scan`.
- ROS 2 LaserScan messages received through `ros_gz_bridge`.
- LiDAR measurements visualised in RViz2.
- A working TF relationship between `base_link` and `laser_link`.

**The virtual LiDAR simulation is now ready for further development**, such as mapping, SLAM and autonomous navigation.
