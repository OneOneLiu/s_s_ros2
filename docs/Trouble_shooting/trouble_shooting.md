# Trouble shooting

1. cannot compile
```bash{.line-numbers}
root@ldh-MS-7B89:/catkin_ws# colcon build
Starting >>> ur_dashboard_msgs
Starting >>> ur_moveit_config
Finished <<< ur_moveit_config [0.13s]                                                                   
Finished <<< ur_dashboard_msgs [0.75s]                     
Starting >>> ur_controllers
--- stderr: ur_controllers                             
/catkin_ws/src/Universal_Robots_ROS2_Driver/ur_controllers/src/scaled_joint_trajectory_controller.cpp: In member function ‘virtual controller_interface::return_type ur_controllers::ScaledJointTrajectoryController::update(const rclcpp::Time&, const rclcpp::Duration&)’:
/catkin_ws/src/Universal_Robots_ROS2_Driver/ur_controllers/src/scaled_joint_trajectory_controller.cpp:319:16: error: no matching function for call to ‘ur_controllers::ScaledJointTrajectoryController::publish_state(const rclcpp::Time&, trajectory_msgs::msg::JointTrajectoryPoint&, trajectory_msgs::msg::JointTrajectoryPoint&, trajectory_msgs::msg::JointTrajectoryPoint&)’
  319 |   publish_state(time, state_desired_, state_current_, state_error_);
      |   ~~~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
In file included from /catkin_ws/src/Universal_Robots_ROS2_Driver/ur_controllers/include/ur_controllers/scaled_joint_trajectory_controller.hpp:41,
                 from /catkin_ws/src/Universal_Robots_ROS2_Driver/ur_controllers/src/scaled_joint_trajectory_controller.cpp:41:
/opt/ros/humble/include/joint_trajectory_controller/joint_trajectory_controller/joint_trajectory_controller.hpp:264:8: note: candidate: ‘void joint_trajectory_controller::JointTrajectoryController::publish_state(const JointTrajectoryPoint&, const JointTrajectoryPoint&, const JointTrajectoryPoint&)’
  264 |   void publish_state(
      |        ^~~~~~~~~~~~~
/opt/ros/humble/include/joint_trajectory_controller/joint_trajectory_controller/joint_trajectory_controller.hpp:264:8: note:   candidate expects 3 arguments, 4 provided
gmake[2]: *** [CMakeFiles/ur_controllers.dir/build.make:76: CMakeFiles/ur_controllers.dir/src/scaled_joint_trajectory_controller.cpp.o] Error 1
gmake[2]: *** Waiting for unfinished jobs....
gmake[1]: *** [CMakeFiles/Makefile2:223: CMakeFiles/ur_controllers.dir/all] Error 2
gmake: *** [Makefile:146: all] Error 2
---
Failed   <<< ur_controllers [7.51s, exited with code 2]

Summary: 2 packages finished [8.44s]
  1 package failed: ur_controllers
  1 package had stderr output: ur_controllers
  3 packages not processed
root@ldh-MS-7B89:/catkin_ws# 
```
- https://robotics.stackexchange.com/questions/110644/ros2-ur-driver-package-failed-ur-controllers
- https://github.com/UniversalRobots/Universal_Robots_ROS2_Driver/issues/904

Unsolved: try to install the release version

2. moveit2 setup assistant 卡死
与这个描述的一致, 必须得打开某个已经source的package里面的urdf文件才行,否则就会卡死. 

3. ros2 control failed loading after adding gripper

```bash{.line-numbers}
[move_group-3] You can start planning now!
[move_group-3] 
[ERROR] [ros2_control_node-5]: process has died [pid 49738, exit code -6, cmd '/opt/ros/humble/lib/controller_manager/ros2_control_node --ros-args --params-file /tmp/launch_params_u12ksnak --params-file /catkin_ws/install/robotiq_moveit_config_test/share/robotiq_moveit_config_test/config/ros2_controllers.yaml'].
```

```bash{.line-numbers}
[gripper_controller]: 'joints' parameter is empty.
```

这个是`moveit2`的`bug`导致的, `robotiq`只有一个关节,所以生成`ros2_controller.yaml`的时候时它写成了joint, 但是应该写成joints.

生成的版本:

```yaml{.line-numbers}
gripper_controller:
  ros__parameters:
    joint: robotiq_85_left_knuckle_joint
    command_interfaces:
      - position
    state_interfaces:
      - position
      - velocity
```

正确的版本:
```yaml{.line-numbers}
gripper_controller:
  ros__parameters:
    joints:
      - robotiq_85_left_knuckle_joint
    command_interfaces:
      - position
    state_interfaces:
      - position
      - velocity
```

另外现在不能像ROS1那样把所有的关节都添加到joint group里面用来预览,不知道后面会不会修复.

- https://robotics.stackexchange.com/questions/111086/ros2-controllers-activation-issues

- https://answers.ros.org/question/418186/ros2_control_node-dies-after-launch/
- https://answers.ros.org/question/416055/unable-to-execute-motion-plan-in-moveit-2-and-ros2-controller-manager-keeps-dying/


其他两个不影响的问题:

```
[moveit_ros_visualization.motion_planning_frame]: Action server: /recognize_objects not available
```
下面这个应该是rviz的问题: https://github.com/ros2/rviz/issues/872, 在我这里应该是夹爪里的某个关节, 单独用机器人没这个错误.
```
[rviz2-4] [ERROR] [1724000877.116674969] [rviz2]: The link is static or has unrealistic inertia, so the equivalent inertia box will not be shown.```