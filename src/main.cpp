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
public:
    ros::NodeHandle nh;

    vision(){
        image_transport::ImageTransport it(nh);
        image_subscriber = it.subscribe("/sumo/camera1/image_raw", 1, &vision::imageCallback, this);
        image_publisher = it.advertise("/sumo/camera1/line_image",1);
    }
    void imageCallback(const sensor_msgs::ImageConstPtr &msg) {
        try {
            //const cv::Mat image = cv_bridge::toCvShare(msg, "bgr8")->image;
            cv_bridge::CvImagePtr cv_ptr;
            cv_bridge::CvImagePtr cdst;
            cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
            //cv::imshow("Display window", image);
            // Detect Field Lines (Copy from simulink)

            cv_ptr = cv_bridge::cvtColor(cv_ptr,"mono8");//cvtColor(cv_ptr->image, cdst->image, CV_BGR2GRAY);
            cv::threshold(cv_ptr->image,cv_ptr->image, 100, 255,0);
            //cv::rectangle(cv_ptr->image, cv::Point(0,0), cv::Point(800,400), cv::Scalar(0, 0, 0), -1, 8);
            image_publisher.publish(cv_ptr->toImageMsg());

            //sensor_msgs::ImagePtr message = cv_bridge::CvImage(std_msgs::Header(), "bgr8", cdst).toImageMsg();
            //if(image_publisher.getNumSubscribers() > 1){

            //image_publisher.publish(message);

        } catch (const cv_bridge::Exception &e) {
            ROS_ERROR_STREAM("CV Exception" << e.what());
        }

    }

};

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
