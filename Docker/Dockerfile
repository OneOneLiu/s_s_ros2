FROM osrf/ros:humble-desktop-full
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

RUN echo "ALL Done"