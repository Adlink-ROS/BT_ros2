# BT on ROS2

The packages is a demo of how to use Behavior Tree to control AMR.

# Installation
* Clone GitHub repo
```bash
# Source dashing environment
mkdir -p ~/bt_ros2_ws/src
cd ~/bt_ros2_ws
wget https://raw.githubusercontent.com/Adlink-ROS/BT_ros2/dashing-devel/bt_ros2.repos
vcs import src < bt_ros2.repos
```
* Install dependencies
```bash
# Source ROS 2 dashing environment
cd ~/bt_ros2_ws
rosdep install --from-paths src --ignore-src -r -y
```
* Build
```bash
colcon build --symlink-install
```

# Usage
## interrupt
We use [NeuronBot2](https://github.com/Adlink-ROS/neuronbot2/tree/dashing-devel) as example.
We will run Gazebo with NeuronBot2 and show a simple BT example.

The BT example (refer to [bt_nav_mememan_interrupt.xml](https://raw.githubusercontent.com/Adlink-ROS/BT_ros2/dashing-devel/bt_xml/bt_nav_mememan_interrupt.xml)) will make NeuronBot2 move between Goal_a and Goal_b.
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
ros2 launch neuronbot2_nav neuronbot2_nav.launch.py map:=$HOME/neuronbot2_ros2_ws/src/neuronbot2/neuronbot2_nav/map/mememan.yaml open_rviz:=true use_sim_time:=true
```
* Open 3rd termainal and run BT.
```bash
source /opt/ros/<ROS2_DISTRO>/local_setup.bash
source ~/bt_ros2_ws/install/local_setup.bash
ros2 run bt_ros2 bt_ros2 bt_xml:=$HOME/bt_ros2_ws/src/BT_ros2/bt_xml/bt_nav_mememan_interrupt.xml
```
* Open 4th terminal and pub interrupt event.
```bash
source /opt/ros/<ROS2_DISTRO>/local_setup.bash
ros2 topic pub -1 /interrupt_event std_msgs/msg/String data:\ \'gohome\'
```
