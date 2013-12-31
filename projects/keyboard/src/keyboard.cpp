#include <ros/ros.h>
#include <signal.h>
#include <termios.h>
#include <stdio.h>
#include "std_msgs/String.h"
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/Quaternion.h>
//#include <conio.h>


#define KEYCODE_0 0x30
#define KEYCODE_1 0x31
#define KEYCODE_2 0x32
#define KEYCODE_3 0x33
#define KEYCODE_4 0x34
#define KEYCODE_5 0x35

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

class Keyboard_Test
{
public:
  //TeleopTurtle();
  void keyLoop();

private:
  ros::NodeHandle nh_;

  ros::Publisher vel_pub_;

};

/*TeleopTurtle::TeleopTurtle():
  linear_(0),
  angular_(0),
  l_scale_(2.0),
  a_scale_(2.0)
{
  nh_.param("scale_angular", a_scale_, a_scale_);
  nh_.param("scale_linear", l_scale_, l_scale_);

  vel_pub_ = nh_.advertise<turtlesim::Velocity>("turtle1/command_velocity", 1);
}
*/
int kfd = 0;
struct termios cooked, raw;

void quit(int sig)
{
  tcsetattr(kfd, TCSANOW, &cooked);
  ros::shutdown();
  exit(0);
}


int main(int argc, char** argv)
{

  ros::init(argc, argv, "keyboard_test");

  Keyboard_Test keyboard_test;

  signal(SIGINT,quit);

  ros::param::set("/object",0);
  keyboard_test.keyLoop();

  return(0);
}


void Keyboard_Test::keyLoop()
{
  char c;
  bool dirty=false;


  // get the console in raw mode
  tcgetattr(kfd, &cooked);
  memcpy(&raw, &cooked, sizeof(struct termios));
  raw.c_lflag &=~ (ICANON | ECHO);
  // Setting a new line, then end of file
  raw.c_cc[VEOL] = 1;
  raw.c_cc[VEOF] = 2;
  tcsetattr(kfd, TCSANOW, &raw);

  puts("Reading from keyboard");
  puts("---------------------------");
  puts("Use the arrow key");

 // vel_pub_=nh_.advertise<std_msgs::String>("Action",1000);
  std_msgs::String msgs;

  std::string ss;
  nh_.param<std::string>("param_flag",ss,"nothing done");

 // MoveBaseClient ac("move_base", true);

 //while(!ac.waitForServer(ros::Duration(5.0))){
  //  ROS_INFO("Waiting for the move_base action server to come up");
 // }

  move_base_msgs::MoveBaseGoal goal;

  for(;;)
  {
    // get the next event from the keyboard
    if(read(kfd, &c, 1) < 0)
    {
      perror("read():");
      exit(-1);
    }

//    linear_=angular_=0;
    ROS_INFO("value: 0x%02X\n", c);
   // printf("c=%c",c);
    switch(c)
    {
      case KEYCODE_1:
      ros::param::set("/object",1);
        break;
      case KEYCODE_2:
      ros::param::set("/object",2);
        break;
      case KEYCODE_3:
      ros::param::set("/object",3);
        break;
      case KEYCODE_4:
      ros::param::set("/object",4);
       break;
      case KEYCODE_5:
      ros::param::set("/object",5);
       break;
      case KEYCODE_0:
      ros::param::set("/object",0);

        break;
    }



  }


  return;
}




