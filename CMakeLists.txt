cmake_minimum_required(VERSION 3.0.2)
project(sumo)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
        roscpp
        sensor_msgs
        std_msgs
        cv_bridge
        image_transport)

catkin_package()
find_package(catkin REQUIRED COMPONENTS
        ${PKG_DEPS}
        ${OpenCV_INCLUDE_DIRS})

find_package(OpenCV 4.2.0 REQUIRED)

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(include
        ${catkin_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
        )

add_executable(my_publisher src/main.cpp)
target_link_libraries(my_publisher
        ${catkin_LIBRARIES}
        ${OpenCV_INCLUDE_DIRS}
        )

