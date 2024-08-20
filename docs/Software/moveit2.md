# Moveit2 Basics

- 可以使用 use collision_aware ik来在拖拽时就避障.
- If the “Use Cartesian Path” checkbox is activated, the robot will attempt to move the end effector **linearly** in cartesian space.
- 在写launch文件构建moveit config的时候, 会自动添加 moveit_config后缀, 只写前面的名字就行了. 比如 robot_gripper_moveit_config. 只写 robot_gripper就行
```python{.line-numbers}
def generate_launch_description():
    moveit_config = MoveItConfigsBuilder("robot_gripper").to_moveit_configs()
    ...
```