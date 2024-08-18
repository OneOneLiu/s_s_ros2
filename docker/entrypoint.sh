#!/bin/bash
# entrypoint.sh

# 移动到工作空间文件夹
source /opt/ros/humble/setup.bash
cd /catkin_ws
colcon build --symlink-install
source /catkin_ws/install/setup.bash

# 执行容器的主命令
exec "$@"