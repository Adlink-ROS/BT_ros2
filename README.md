# BT on ROS2

The packages is a demo of how to use Behavior Tree to control AMR.

# Build
1. git clone the repo.
```
mkdir -p ~/bt_ros2_ws/src
cd ~/bt_ros2_ws/src
git clone https://github.com/Adlink-ROS/BT_ros2.git
```
2. Install dependencies
```
source /opt/ros/<ROS2_DISTRO>/setup.bash
cd ~/bt_ros2_ws
rosdep install --from-paths src --ignore-src -r -y
```
3. Build
```
colcon biuld --symlink-install
```

# Usage
We use [NeuronBot2](https://github.com/Adlink-ROS/neuronbot2/tree/foxy-devel) as example.
We will run Gazebo with NeuronBot2 and show a simple BT example.

The BT example (refer to [bt_nav_mememan_interrupt.xml](https://raw.githubusercontent.com/Adlink-ROS/BT_ros2/foxy-devel/bt_xml/bt_nav_mememan_interrupt.xml)) will make NeuronBot2 move between Goal_a and Goal_b.
If receiving /interrupt_event, which is gohome, then NeuronBot2 will move to Goal_c.

* Open 1st terminal and run mememan world.
```
source /opt/ros/<ROS2_DISTRO>/setup.bash
source ~/neuronbot2_ros2_ws/install/local_setup.bash
ros2 launch neuronbot2_gazebo neuronbot2_world.launch.py world_model:=mememan_world.model
```
* Open 2nd terminal and run navigation.
```
source /opt/ros/<ROS2_DISTRO>/setup.bash
source ~/neuronbot2_ros2_ws/install/local_setup.bash
ros2 launch neuronbot2_nav bringup_launch.py map:=$HOME/neuronbot2_ros2_ws/src/neuronbot2/neuronbot2_nav/map/mememan.yaml open_rviz:=true use_sim_time:=true
```
* Open 3rd termainal and run BT.
```
source /opt/ros/<ROS2_DISTRO>/setup.bash
source ~/bt_ros2_ws/install/local_setup.bash
ros2 run bt_ros2 bt_ros2 --ros-args -p bt_xml:=$HOME/bt_ros2_ws/src/BT_ros2/bt_xml/bt_nav_mememan_interrupt.xml
```
* Open 4th terminal and pub interrupt event.
```
ros2 topic pub /interrupt_event std_msgs/String "gohome"
```
