# BT on ROS2

The packages is a demo of how to use Behavior Tree to control AMR.

# Build
```
mkdir -p ~/bt_ros2_ws/src
cd ~/bt_ros2_ws/src
git clone https://github.com/Adlink-ROS/BT_ros2.git
source /opt/ros/foxy/setup.bash
rosdep install --from-paths src --ignore-src -r -y
colcon biuld --symlink-install
```

# Usage
```
source /opt/ros/foxy/setup.bash
soruce ~/bt_ros2_ws/install/local_setup.bash
ros2 run bt_ros2 bt_ros2 --ros-args -p bt_xml:=<absolute_path_to_bt_xml>
```
