#include <iostream>
#include "ros/ros.h"
#include "std_msgs/Float64.h"

int main(int argc, char **argv) {
  ros::init(argc, argv, "epic_node");
  ros::NodeHandle n;

  ros::Publisher frontLeftWheelPub = n.advertise<std_msgs::Float64>("front_left_arm_controller/command", 1000);
  ros::Publisher frontRightWheelPub = n.advertise<std_msgs::Float64>("front_right_arm_controller/command", 1000);
  ros::Publisher backRightWheelPub = n.advertise<std_msgs::Float64>("back_right_arm_controller/command", 1000);
  ros::Publisher backLeftWheelPub = n.advertise<std_msgs::Float64>("back_left_arm_controller/command", 1000);

  ros::Publisher frontLeftWheelPubTurn = n.advertise<std_msgs::Float64>("front_left_arm_controller_turn/command", 1000);
  ros::Publisher frontRightWheelPubTurn = n.advertise<std_msgs::Float64>("front_right_arm_controller_turn/command", 1000);
  ros::Publisher backRightWheelPubTurn = n.advertise<std_msgs::Float64>("back_right_arm_controller_turn/command", 1000);
  ros::Publisher backLeftWheelPubTurn = n.advertise<std_msgs::Float64>("back_left_arm_controller_turn/command", 1000);
  std_msgs::Float64 initialPos;
  initialPos.data = 0.0;
  frontRightWheelPubTurn.publish(initialPos);
  frontLeftWheelPubTurn.publish(initialPos);
  backLeftWheelPubTurn.publish(initialPos);
  backRightWheelPubTurn.publish(initialPos);

  while (ros::ok()){
      std_msgs::Float64 velocityMsg;
      std_msgs::Float64 positionMsg;

      char in, direction;
      std::cout << "Press 'w' to move, 's' to rotate, and 'e' to exit:";
      std::cin  >> in;
      switch (in){
          case 'w':
              std::cout << "Please enter velocity:";
              std::cin >> velocityMsg.data;
              frontLeftWheelPub.publish(velocityMsg);
              frontRightWheelPub.publish(velocityMsg);
              backRightWheelPub.publish(velocityMsg);
              backLeftWheelPub.publish(velocityMsg);
              break;
          case 's':
              std::cout << "'f' for front and 'b' for back";
              std::cin >> direction;

              std::cout << "Please enter angle in radians:";
              std::cin >> positionMsg.data;

              if (direction == 'f'){
                  frontRightWheelPubTurn.publish(positionMsg);
                  frontLeftWheelPubTurn.publish(positionMsg);
              }
              else{
                  backLeftWheelPubTurn.publish(positionMsg);
                  backRightWheelPubTurn.publish(positionMsg);
              }
              break;
          case 'e':
              return 0;
      }


  }
  return 0;
}
