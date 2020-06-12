# BT on ROS2

The packages is a demo of how to use Behavior Tree to control AMR.

# Installation
```
mkdir -p ~/bt_ros2_ws/src
cd ~/bt_ros2_ws/
wget https://gist.githubusercontent.com/airuchen/3ecdab72304f3e02fc54c0f0b8396acc/raw/031d8e02361520225cc8e82d1e08ed4a428396c9/bt_ros2.repos
vcs import src < bt_ros2.repos
source /opt/ros/dashing/setup.bash
rosdep install --from-paths src --ignore-src -r -y
colcon biuld --symlink-install
```

# Usage
```
source /opt/ros/dashing/setup.bash
soruce ~/bt_ros2_ws/install/local_setup.bash
ros2 run bt_ros2 bt_ros2 _bt_xml:=<absolute_path_to_bt_xml>
```
