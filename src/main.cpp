#include "ros/ros.h"
#include "std_msgs/Float64.h"

#include <iostream>
// Include opencv3
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
// Include CvBridge, Image Transport, Image msg
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>

class vision{
    image_transport::Subscriber image_subscriber;
    image_transport::Publisher image_publisher;
    ros::Publisher color_publisher;
    ros::Publisher leftWheelPub ;
    ros::Publisher rightWheelPub ;

public:
    ros::NodeHandle nh;
    float leftSpeed = -1.0;
    float rightSpeed = -1.0;
    vision(){
        image_transport::ImageTransport it(nh);
        image_subscriber = it.subscribe("/sumo/camera1/image_raw", 1, &vision::imageCallback, this);
        image_publisher = it.advertise("/sumo/camera1/line_image",1);
        leftWheelPub = nh.advertise<std_msgs::Float64>("/sumo_left_wheel_controller/command", 1000);
        rightWheelPub = nh.advertise<std_msgs::Float64>("/sumo_right_wheel_controller/command", 1000);
    }
    void imageCallback(const sensor_msgs::ImageConstPtr &msg) {
        try {

            cv_bridge::CvImagePtr cv_ptr;
            cv_bridge::CvImagePtr cdst;
            cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);


            cv_ptr = cv_bridge::cvtColor(cv_ptr,"mono8");//Grey scale
            cv::threshold(cv_ptr->image,cv_ptr->image, 100, 255,0);// threshold
            cv::rectangle(cv_ptr->image, cv::Point(0,0), cv::Point(800,400), cv::Scalar(0, 0, 0), -1, 8);//draw rectangle
            image_publisher.publish(cv_ptr->toImageMsg());


            CvScalar color = cv_ptr->image.at<uchar>(cv::Point(400,700));

            printf("%f\n", color.val[0]);//Prints the color of the pixel. Black is 0, White is 255

            //Here add a way of controlling the robot movement to follow the line based on the color of the pixel





        } catch (const cv_bridge::Exception &e) {
            ROS_ERROR_STREAM("CV Exception" << e.what());
        }

    }



};

void colorCallback (const std_msgs::Float64 msg) {


}
int main(int argc, char **argv) {
    ros::init(argc, argv, "test");

    vision hi;

    ros::spin();



    return 0;
}
/*int main(int argc, char **argv) {
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
}*/
