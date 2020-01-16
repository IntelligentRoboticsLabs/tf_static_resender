cmake_minimum_required(VERSION 2.8.3)
project(tf_static_resender)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++17)

find_package(catkin REQUIRED)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  tf2_msgs)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES tf_static_resender
CATKIN_DEPENDS roscpp std_msgs tf2_msgs
#  DEPENDS system_lib
)

include_directories( ${catkin_INCLUDE_DIRS} )

add_executable(tf_static_resender src/tf_static_resender.cpp)
target_link_libraries(tf_static_resender ${catkin_LIBRARIES})