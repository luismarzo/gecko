#include <ros/ros.h>
#include "std_msgs/Float64MultiArray.h"
#include <signal.h>
#include <termios.h>
#include <stdio.h>
#include <vector>

#define KEYCODE_RIGHT 0x43
#define KEYCODE_LEFT 0x44
#define KEYCODE_UP 0x41
#define KEYCODE_DOWN 0x42
#define KEYCODE_A 0x61
#define KEYCODE_D 0x64
#define KEYCODE_S 0x73
#define KEYCODE_W 0x77
#define KEYCODE_Q 0x71
#define KEYCODE_E 0x65
#define KEYCODE_SPACE 0x20

using namespace std;

class TeleopGecko
{
public:
  TeleopGecko();
  void keyLoop();

private:
  ros::NodeHandle nh_;
  vector<double> vec = { 0,0};
  float _cnt_h=0;
  float _cnt_v=0;
  ros::Publisher _pub;
};

TeleopGecko::TeleopGecko()
{



  _pub = nh_.advertise<std_msgs::Float64MultiArray>("/gecko/camera_position_controller/command", 1000);
}

int kfd = 0;
struct termios cooked, raw;

void quit(int sig)
{
  (void)sig;
  tcsetattr(kfd, TCSANOW, &cooked);
  ros::shutdown();
  exit(0);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "key_teleop");
  TeleopGecko teleop_turtle;

  signal(SIGINT,quit);

  teleop_turtle.keyLoop();

  return(0);
}

void TeleopGecko::keyLoop()
{
  char c;
  bool dirty=false;

  tcgetattr(kfd, &cooked);

  memcpy(&raw, &cooked, sizeof(struct termios));

  raw.c_lflag &=~ (ICANON | ECHO);
  raw.c_cc[VEOL] = 1;
  raw.c_cc[VEOF] = 2;
  tcsetattr(kfd, TCSANOW, &raw);

  puts("Reading from keyboard");
  puts("---------------------------");
  puts("Use arrow keys to move the rbcar.");

  int i;
  for(;;){
    if(read(kfd, &c, 1) < 0) {
      perror("read():");
      exit(-1);
    }


    ROS_DEBUG("value: 0x%02X\n", c);

    std_msgs::Float64MultiArray msg;

    switch(c) {


      case KEYCODE_RIGHT:
	_cnt_h=_cnt_h-0.1;
	if(_cnt_h<-0.2){_cnt_h=-0.2;}

	dirty = true;

        break;

      case KEYCODE_LEFT:
      	_cnt_h=_cnt_h+0.1;
	if(_cnt_h>0.2){_cnt_h=0.2;}      
	dirty = true;
        break;

      case KEYCODE_UP:
	_cnt_v=_cnt_v-0.1;
	if(_cnt_v<-0.7){_cnt_v=-0.7;}
	dirty = true;
        break;

      case KEYCODE_DOWN:
	_cnt_v=_cnt_v+0.1;
	if(_cnt_v>0.1){_cnt_v=0.1;}
	dirty = true;
        break;

      case KEYCODE_SPACE:


        dirty = true;
        break;
    }


    if(dirty ==true)
    {	 std::cout<<_cnt_v<<","<<_cnt_h<<std::endl;
    	 vec = { _cnt_v, _cnt_h};
         msg.layout.dim.push_back(std_msgs::MultiArrayDimension());  
   	 msg.layout.dim[0].size = vec.size();
   	 msg.layout.dim[0].stride = 1;
   	 msg.layout.dim[0].label = "wow";


   	 msg.data.clear();
   	 msg.data.insert(msg.data.end(), vec.begin(), vec.end());
    
      _pub.publish(msg);
      dirty=false;
    }
  }

  return;
}
