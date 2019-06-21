cmake_minimum_required(VERSION 2.8.3)
project(gecko_control)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  genmsg
  gazebo_msgs
  gazebo_plugins
  message_generation
)

find_package(ignition-math5 REQUIRED)

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

#add_library(RosFlashLightPlugin SHARED src/RosFlashLightPlugin.cc)
#target_link_libraries(RosFlashLightPlugin ${GAZEBO_LIBRARIES} ${catkin_LIBRARIES}) 
#target_link_libraries(RosFlashLightPlugin
#  ${catkin_LIBRARIES}
#  LedPlugin
#)

#add_library(LightVisualPlugin src/LightVisualPlugin.cc)
#target_link_libraries(LightVisualPlugin
#  ${catkin_LIBRARIES}
#   ${GAZEBO_LIBRARIES}
#)

#add_library(LedPlugin src/LedPlugin.cc)
#target_link_libraries(LedPlugin
#  ${catkin_LIBRARIES}
#   ${GAZEBO_LIBRARIES}
   
#)

#add_library(FlashLightPlugin src/FlashLightPlugin.cc)
#target_link_libraries(FlashLightPlugin
#  ${catkin_LIBRARIES}
#   ${GAZEBO_LIBRARIES}
#)



add_executable(gecko_movement src/gecko_movement.cpp)
target_link_libraries(gecko_movement ${catkin_LIBRARIES})
add_dependencies(gecko_movement gecko_control_gencpp)

add_executable(gecko_teleop src/gecko_teleop.cpp)
target_link_libraries(gecko_teleop ${catkin_LIBRARIES})
add_dependencies(gecko_teleop gecko_teleop_gencpp)

