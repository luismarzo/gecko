#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float64MultiArray.h"
#include <vector>

#include <sstream>
using namespace std;

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{
 
  ros::init(argc, argv, "gecko_movement_publisher");

  ros::NodeHandle n;

  ros::Publisher chatter_pub = n.advertise<std_msgs::Float64MultiArray>("/gecko/gecko_group_position_controller/command", 1000);

  ros::Rate loop_rate(10);


  double count = 0;
  vector<double> vec;
  vector<double> vec1 = { 0,0,0,0};
  while (ros::ok())
  {
    int i = 0;
    std_msgs::Float64MultiArray msg;
    vec1 = { count, count, count, count};

    msg.layout.dim.push_back(std_msgs::MultiArrayDimension());  
    msg.layout.dim[0].size = vec.size();
    msg.layout.dim[0].stride = 1;
    msg.layout.dim[0].label = "wow";


    msg.data.clear();
    msg.data.insert(msg.data.end(), vec1.begin(), vec1.end());
    
    chatter_pub.publish(msg);
    ros::spinOnce();

    //clear stuff and sleep
    vec.clear();
    loop_rate.sleep();
    count=count+0.3;
  }


  return 0;
}
