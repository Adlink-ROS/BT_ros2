# BT on ROS2

The packages is a demo of how to use Behavior Tree to control AMR.

# Build
1. git clone the repo.
```bash
mkdir -p ~/bt_ros2_ws/src
cd ~/bt_ros2_ws/src
git clone https://github.com/Adlink-ROS/BT_ros2.git
```
2. Install dependencies
```bash
source /opt/ros/<ROS2_DISTRO>/setup.bash
cd ~/bt_ros2_ws
rosdep install --from-paths src --ignore-src -r -y
```
3. Build
```bash
colcon build --symlink-install
```

# Usage
## interrupt
We use [NeuronBot2](https://github.com/Adlink-ROS/neuronbot2/tree/foxy-devel) as example.
We will run Gazebo with NeuronBot2 and show a simple BT example.

The BT example (refer to [bt_nav_mememan_interrupt.xml](https://raw.githubusercontent.com/Adlink-ROS/BT_ros2/foxy-devel/bt_xml/bt_nav_mememan_interrupt.xml)) will make NeuronBot2 move between Goal_a and Goal_b.
If receiving /interrupt_event, which is gohome, then NeuronBot2 will move to Goal_c.

* Open 1st terminal and run mememan world.
```bash
source /opt/ros/<ROS2_DISTRO>/local_setup.bash
source ~/neuronbot2_ros2_ws/install/local_setup.bash
ros2 launch neuronbot2_gazebo neuronbot2_world.launch.py world_model:=mememan_world.model
```
* Open 2nd terminal and run navigation.
```bash
source /opt/ros/<ROS2_DISTRO>/local_setup.bash
source ~/neuronbot2_ros2_ws/install/local_setup.bash
ros2 launch neuronbot2_nav bringup_launch.py map:=$HOME/neuronbot2_ros2_ws/src/neuronbot2/neuronbot2_nav/map/mememan.yaml open_rviz:=true use_sim_time:=true
```
* Open 3rd termainal and run BT.
```bash
source /opt/ros/<ROS2_DISTRO>/local_setup.bash
source ~/bt_ros2_ws/install/local_setup.bash
ros2 run bt_ros2 bt_ros2 --ros-args -p bt_xml:=$HOME/bt_ros2_ws/src/BT_ros2/bt_xml/bt_nav_mememan_interrupt.xml
```
* Open 4th terminal and pub interrupt event.
```bash
source /opt/ros/<ROS2_DISTRO>/local_setup.bash
ros2 topic pub -1 /interrupt_event std_msgs/msg/String data:\ \'gohome\'
```

## Take snapshot
The demo is to show how to take snapshot with BT example.
You need to install OpenVINO and its ROS 2 wrapper before using the example.

* Open 1st terminal and run OpenVINO object detection
```bash
# Source ROS 2 environment
# Setup OpenVINO environment and source wrapper
ros2 launch dynamic_vino_sample pipeline_object.launch.py
```
* Open 2nd terminal and run image_saver
  - If you don't have image_view, please run `sudo apt install ros-${ROS_DISTRO}-image-view`
```bash
# Source ROS 2 environment
ros2 run image_view image_saver image:=ros2_openvino_toolkit/image_rviz
```
* Open 3rd terminal and run BT
```bash
# Source ROS 2 environment
source ~/bt_ros2_ws/install/local_setup.bash
ros2 run bt_ros2 bt_ros2 --ros-args -p bt_xml:=$HOME/bt_ros2_ws/src/BT_ros2/bt_xml/bt_snapshot.xml
```

# Note
If you want to get the coordinate for navigation, you can run navigation2 and listen to the topic /goal_pose.

The position and orientation should be put into BT file and the orientation value we use here is Quaternion.

If you only has Euler Angle and want to transfer to Quaternion, refer to the online tools, such as https://quaternions.online/
