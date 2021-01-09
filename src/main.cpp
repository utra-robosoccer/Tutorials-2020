#include "ros/ros.h"
#include "std_msgs/Float64.h"

#include <iostream>

int main(int argc, char **argv) {
  ros::init(argc, argv, "talker");
  ros::NodeHandle n;
  
  ros::Publisher leftWheelPub = n.advertise<std_msgs::Float64>("/sumo_left_wheel_controller/command", 1000);
  ros::Publisher rightWheelPub = n.advertise<std_msgs::Float64>("/sumo_right_wheel_controller/command", 1000);
  
  float leftSpeed = 0;
  float rightSpeed = 0;
  
  while (ros::ok())
  {
    // wait for user input
    char input{0};
    std::cin >> input;
    
    switch(input)
    {
      case 'q': leftSpeed -= .5; break;
      case 'e': rightSpeed -= .5; break;
      case 'a': leftSpeed += .5; break;
      case 'd': rightSpeed += .5; break;
      default: leftSpeed = rightSpeed = 0;
    }
    
    // send messages
    std_msgs::Float64 msgLeft, msgRight;
    msgLeft.data = leftSpeed;
    msgRight.data = rightSpeed;
    leftWheelPub.publish(msgLeft);
    rightWheelPub.publish(msgRight);
    std::cout << "current speeds: " << leftSpeed << ", " << rightSpeed << "\n";
  }
  
  return 0;
}
