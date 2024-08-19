xhost local:root
XAUTH=/tmp/.docker.xauth
docker run --rm -it \
    --name=ros_humble_container \
    --env="DISPLAY=$DISPLAY" \
    --env="QT_X11_NO_MITSHM=1" \
    --env="XAUTHORITY=$XAUTH" \
    --volume="/home/$USER/catkin_ws/src/s_s_ros2/src/ur5_robot_gripper:/catkin_ws/src/ur5_robot_gripper" \
    --volume="/home/$USER/catkin_ws/src/s_s_ros2/src/robot_gripper_moveit_config:/catkin_ws/src/robot_gripper_moveit_config" \
    --volume="/dev/bus/usb:/dev/bus/usb" \
    --volume="/tmp/.docker.xauth:/tmp/.docker.xauth:rw" \
    --net=host \
    --privileged \
    ros_humble_image \
    bash

echo "Done."
