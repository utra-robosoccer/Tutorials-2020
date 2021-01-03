#include "ros/ros.h"
#include "std_msgs/Float64.h"

#include <iostream>

int main(int argc, char **argv) {
  
  ros::init(argc, argv, "my_node");

  ros::NodeHandle n;

  ros::Publisher leftPub = n.advertise<std_msgs::Float64>("/left_arm_controller/command", 1000);
  ros::Publisher headPub = n.advertise<std_msgs::Float64>("/head_controller/command", 1000);
  
  float head_position = 0.0;
  char input = 0;
  while(ros::ok()){
    std::cout << "pausing for input\n";
    std::cin >> input;
    
    std_msgs::Float64 leftSpeed;
    std_msgs::Float64 headMsg;
    
    if (input == 'q') {
      //rotate clockwise
      leftSpeed.data = 1.0;
    }
    if (input == 'w') {
      //rotate counter clockwise
      leftSpeed.data = -1.0;
    }
    
    if (input == 'a') {
      //rotate clockwise
      head_position += 0.1;
    }
    if (input == 's') {
      //rotate counter clockwise
      head_position -= 0.1;
    }
    headMsg.data = head_position;
    
    headPub.publish(headMsg);
    leftPub.publish(leftSpeed);
  }
  
  return 0;
}
