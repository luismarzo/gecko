cmake_minimum_required(VERSION 2.8.3)
project(gecko_control)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  genmsg
  gazebo_msgs
  message_generation
)



generate_messages(DEPENDENCIES std_msgs gazebo_msgs)

catkin_package(
 CATKIN_DEPENDS
    roscpp
)


include_directories(
include  ${catkin_INCLUDE_DIRS}
)

find_package(gazebo REQUIRED)
include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})
list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")

find_package(gazebo REQUIRED)



