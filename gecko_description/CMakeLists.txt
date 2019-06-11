cmake_minimum_required(VERSION 2.8.3)
project(gecko_description)

IF(UNIX)
	add_definitions(-std=c++11)
ENDIF()

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)


catkin_package(CATKIN_DEPENDS roscpp std_msgs )


include_directories(

  ${catkin_INCLUDE_DIRS}
)

