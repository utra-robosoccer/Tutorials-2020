#include <iostream>
#include <string>
#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "std_msgs/String.h"

ros::Publisher leftWheelPub, rightWheelPub;

void commandsCallback(const std_msgs::String::ConstPtr& msg) {
  float leftSpeed = 0;
  float rightSpeed = 0;

  std::string command = msg->data;

  if(command == "GO") 
  {
    leftSpeed = -1.0;
    rightSpeed = -1.0;
  }
  else if(command == "GO_REALLY_FAST")
  {
    leftSpeed = -10.0; // radians per second
    rightSpeed = -10.0;
  }
  else if(command == "BACK") 
  {
    leftSpeed = 0.5;
    rightSpeed = 0.5;
  } 
  else if(command == "LEFT") 
  {
    leftSpeed = -1.0;
    rightSpeed = -0.5;
  } 
  else if(command == "RIGHT") 
  {
    leftSpeed = -0.5;
    rightSpeed = -1.0;
  } 
  else 
  {
    leftSpeed = 0.0;  // Stop the robot
    rightSpeed = 0.0;
  }

  // send messages
  std_msgs::Float64 msgLeft, msgRight;
  msgLeft.data = leftSpeed;
  msgRight.data = rightSpeed;
  leftWheelPub.publish(msgLeft);
  rightWheelPub.publish(msgRight);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "motorController");
  ros::NodeHandle n;

  ros::Subscriber commandSub = n.subscribe("motor_commands", 1000, commandsCallback);

  leftWheelPub = n.advertise<std_msgs::Float64>("/left_wheel_controller/command", 1000);
  rightWheelPub = n.advertise<std_msgs::Float64>("/right_wheel_controller/command", 1000);

  ros::spin();

  return 0;
}
