## 创建新的包
1. 进入工作空间的src目录
首先，确保你已经有一个ROS 2工作空间。如果没有，请先创建一个，然后进入工作空间的src目录。

```bash
cd ~/ros2_ws/src
```
2. 使用ros2 pkg create命令新建一个包
使用ros2 pkg create命令可以轻松创建一个新包。你可以指定包名、依赖项以及构建工具（ament_cmake或ament_python等）。

例如，创建一个基于ament_cmake的包：

```bash
ros2 pkg create --build-type ament_cmake my_new_package
```
如果你想创建一个基于Python的包，可以使用ament_python：

```bash
ros2 pkg create --build-type ament_python my_python_package
```
3. 添加依赖项（可选）
在创建包时，你可以直接指定依赖项。依赖项将在package.xml文件和CMakeLists.txt（对于CMake包）或setup.py（对于Python包）中被配置好。

例如，创建一个依赖于rclcpp和std_msgs的CMake包：

```bash
ros2 pkg create --build-type ament_cmake my_new_package --dependencies rclcpp std_msgs
```
4. 查看生成的文件结构
创建包后，ROS 2会自动生成以下文件结构：

```bash
my_new_package/
├── CMakeLists.txt
├── package.xml
├── src/
└── include/
```
对于Python包，文件结构会稍有不同：

```bash
my_python_package/
├── setup.py
├── package.xml
└── my_python_package/
    └── __init__.py
```
5. 构建工作空间
在创建包之后，你需要返回工作空间的根目录，并使用colcon进行构建：

```bash
cd ~/ros2_ws
colcon build
```
6. 更新环境变量
在构建完新的包之后，记得更新环境变量：

```bash
source ~/ros2_ws/install/setup.bash
```
现在你已经成功创建并构建了一个新的ROS 2软件包，可以开始在其中编写代码和配置节点了。

## 给包添加文件
> https://docs.ros.org/en/foxy/Tutorials/Intermediate/URDF/Using-URDF-with-Robot-State-Publisher.html

在setup.py中添加这些:
1. 依赖仓库
```python{.line-numbers}
import os
from glob import glob
from setuptools import setup
from setuptools import find_packages
```

2. **共享的文件** :star:

```python{.line-numbers}
data_files=[
  ...
  (os.path.join('share', package_name, 'launch'), glob(os.path.join('launch', '*launch.[pxy][yma]*'))),
  (os.path.join('share', package_name), glob('urdf/*')),
],
```

> 刚才就是不知道这一步,导致出错了


直接上面这么写是不会保留目录的层级关系的,最好使用这个自定义的函数:
```python{.line-numbers}
def package_files(directory):
    paths = []
    for path, _, files in os.walk(directory):
        for file in files:
            paths.append((os.path.join('share', package_name, path), [os.path.join(path, file)]))
    return paths
...

data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'), glob(os.path.join('launch', '*launch.[pxy][yma]*'))),
    ] + package_files('urdf') + package_files('meshes'),

```
就可以了.

3. 添加可执行文件
```python{.line-numbers}
'console_scripts': [
    'state_publisher = urdf_tutorial_r2d2.state_publisher:main'
],
```

## 如何launch
https://docs.ros.org/en/rolling/Tutorials/Intermediate/Launch/Creating-Launch-Files.html