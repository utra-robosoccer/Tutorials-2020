# Winter Break Tutorials

- The publisher portion is based on this [ROS tutorial](https://wiki.ros.org/ROS/Tutorials/WritingPublisherSubscriber%28c%2B%2B%29)

## Prerequisites
- have ubuntu and ROS installed

## Cloning the repo
From home directory create /catkin_ws/src folder and run the following command
```
mkdir -p catkin_ws/src
cd catkin_ws/src
git clone https://github.com/utra-robosoccer/Tutorials-2020.git
```

## Switch To computer_vision branch
```
git switch computer_vision
```

## Updating Dependencies
```
cd ~/catkin_ws/
rosdep update
rosdep install --from-paths src --ignore-src -r -y --rosdistro noetic
```

## Building tutorial package
Sourcing setup file so helps the system know where to look for your built files
```
cd ~/catkin_ws
catkin build computer_vision_pkg
source devel/setup.bash
```

## Launch the robot
```
roslaunch computer_vision_pkg gazebo.launch
```

## Commands used during tutorial
useful tip: press tab to auto-complete words as you type commands
Open a new terminal to run commands for the robot

```
cd ~/catkin_ws
source devel/setup.bash
```
To run the main node run this command
```
rosrun sumo my_publisher
```

To send a command to the left arm
```
rostopic pub /sumo_left_wheel_controller/command std_msgs/Float64 "data: 1.0"
```

To see the ROS node tree run this command
```
rqt_graph
```

To see the RVIZ node  run this command
```
rviz
```
