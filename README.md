# Tutorials-2020
Winter Break Tutorials

To launch the robot first build the project and source the setup file
```
cd ~/catkin_ws
catkin build tutorial
source devel/setup.bash
```

Finally you can launch the robot
```
roslaunch tutorial gazebo.launch
```

To run the main node run this command
```
rosrun tutorial my_publisher
```
