FROM osrf/ros:iron-desktop-full
# Set the environment variable to non-interactive, this is to avoid the tzdata configuration during the installation of the packages
ENV DEBIAN_FRONTEND=noninteractive

# System layer installation
RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y wget && \
    apt-get install -y iputils-ping && \
    apt-get -y install build-essential && \
    apt install -y cmake && \
    apt install -y tree && \
    apt install -y gdb && \
    apt-get install -y git && \
    apt-get install -y python3-pip && \
    apt-get install -y xauth x11-apps # This is for GUI testing

# Install realsense2_camera
RUN apt install -y ros-$ROS_DISTRO-librealsense2* && \
    apt install -y ros-$ROS_DISTRO-realsense2-*

# Install UR5 robot
RUN mkdir -p /catkin_ws/src && \
    cd /catkin_ws/src && \
    apt install -y ros-${ROS_DISTRO}-ros2-control && \
    apt install -y ros-${ROS_DISTRO}-ament-cmake && \
    apt install -y ros-${ROS_DISTRO}-gazebo-ros-pkgs && \
    apt-get install -y ros-${ROS_DISTRO}-ur && \
    apt-get install -y ros-${ROS_DISTRO}-ur-bringup

RUN cd /catkin_ws/ && \
    rosdep update && \
    rosdep install --from-paths src --ignore-src -r -y && \
    colcon build --symlink-install

COPY entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]
CMD ["bash"]

# Automatically source
RUN echo "source /opt/ros/iron/setup.bash" >> ~/.bashrc && \
    echo "source /catkin_ws/install/setup.bash" >> ~/.bashrc

RUN echo "ALL Done"