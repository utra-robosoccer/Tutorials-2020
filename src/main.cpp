#include <iostream>
#include "ros/ros.h"
#include "std_msgs/Float64.h"

int main(int argc, char **argv) {
  std::cout << "Hello World!\n";

  ros::init(argc, argv, "my_little_nod");

  ros::NodeHandle n;

  ros::Publisher armPub = n.advertise<std_msgs::Float64>("left_arm_controller/command", 1000);

  while(ros::ok()) {
      char in;
      std::cout << "Please enter a value";
      std:: cin >> in;
      std_msgs::Float64 speedMsg;

      switch (in)
      {
          case 'a':
          speedMsg.data = 1.0;
          break;
          case 's':
          speedMsg.data =  0.0;
          break;
          case 'd':
              speedMsg.data = -1.0;
              break;
      }

      armPub.publish(speedMsg);
  }

  return 0;
}
