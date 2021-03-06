# Winter Break Tutorials

- Slides can be found [here](https://docs.google.com/presentation/d/13XCDx3GYOWQLYuZl6OiorKB5LQHKp4tY2wDdE2C2mO4/edit#slide=id.p).
- The urdf portion is based on this [ROS tutorial](https://wiki.ros.org/urdf/Tutorials/Building%20a%20Visual%20Robot%20Model%20with%20URDF%20from%20Scratch)
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

## Updating Dependencies
```
cd ~/catkin_ws/
rosdep update
rosdep install --from-paths src --ignore-src -r -y --rosdistro noetic
```

## Installing Controllers For Robot
```
sudo apt-get update
sudo apt-get install ros-noetic-ros-controllers
```


## Building tutorial package
First build the project and source the setup file so that the system knows where to look for your build files
```
cd ~/catkin_ws
catkin build sumo
source devel/setup.bash
```

## Launch the robot
```
roslaunch sumo gazebo.launch
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
To enter the config for rviz go to
```
The top right on file, click open config then go to and select /home/manx52/catkin_ws/src/Tutorials-2020/config/config.rviz
```
