/*
 * Copyright (C) 2008, Morgan Quigley and Willow Garage, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the names of Stanford University or Willow Garage, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specif multiple definition of `main'
ic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

// %Tag(FULLTEXT)%
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "msg_kinect/esangles.h"



    #include <octave/oct.h>
    #include <octave/octave.h>
    #include <octave/parse.h>
    #include <octave/toplev.h>
    #include <stdio.h>

/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
// %Tag(CALLBACK)%


class Hmm
{
public:
  //TeleopNaoNi();
     void chatterCallback(const msg_kinect::esangles& msg);
    // octave_value_list foutput;
     octave_value_list foutput1;
    // octave_value finput;
     octave_value_list finput;

     Matrix data, alpha, alpha_1;
    // float gesture;
     int cnt, object;
     Hmm(int,int);
     int cnt2, cnt3;
     int value1, value2, value3;
     //int obs_p;
     int obs_p1, obs_p2, tmp;
     float lik1, lik2, lik3;
    // int dtw1, dtw2, dtw3;
    //  float dis1, dis2, dis3;
     clock_t start, end;
     int valuel;
     ros::NodeHandle n;

   //  ros::Publisher pub = nh.advertise<std_msgs::String>("gesture", 5);
      msg_kinect::esangles ges;
      ros::Publisher pub;
     //float dataset[10];
    // void init();
};

Hmm::Hmm(int a,int b)
     {
         cnt = a;
         cnt2 = b;
         cnt3 = a;
         data = Matrix(20,4);
         alpha = Matrix(1,7);
         alpha_1 = Matrix(1,7);
         obs_p1=7;
         obs_p2=7;
        //int tmp;
//         slide_start = 0;
         pub = n.advertise<msg_kinect::esangles>("talker", 1000);

     }
//void Hmm::init(){cnt=0; data = Matrix(10,4);}
void Hmm::chatterCallback(const msg_kinect::esangles& msg)
{
   // FILE *pFile;
ros::param::get("/object", object);
if (msg.leroll!= 0)
     //continue;
{//comment here
        if (cnt<15)//collecting data
      {

      // dataset[cnt] = angles;

       data(cnt,0) = float(msg.leroll);
       data(cnt,1) = float(msg.leyaw);
       data(cnt,2) = float (msg.lsroll);
       data(cnt,3) = float (msg.lspitch);
  //     alpha(1,0) = 0.25;
    //   alpha(1,1) = 0.25;
    //   alpha(1,2) = 0.25;
     //  alpha(1,3) = 0.25;
       cnt = cnt + 1 ;

      }
      else
      {



         if (cnt2==0)
         {

       alpha(1,0) = 0.25;
       alpha(1,1) = 0.25;
       alpha(1,2) = 0.25;
       alpha(1,3) = 0.25;
       alpha(1,4) = 0.25;
       alpha(1,5) = 0.25;
       alpha(1,6) = 0.3;
         finput(0)= data;
         finput(1) = object;
         finput(2) = alpha;
         finput(3) = obs_p1;
         cnt2 = cnt2 + 1;
         }

         else
         {
         finput(0)= data;
         finput(1) = object;
         finput(2) = alpha_1;
         finput(3)=obs_p1;
         }



     foutput1 = feval("bayesian", finput);
     value1  = foutput1(0).double_value();
     lik1 = foutput1(1).double_value();
     //alpha_1  = foutput1(2).matrix_value();
     value2 = foutput1(2).double_value();
     lik2 = foutput1(3).double_value();
     value3 = foutput1(4).double_value();
     lik3 = foutput1(5).double_value();
     alpha_1 = foutput1(6).matrix_value();
     tmp = foutput1(7).double_value();
     if ((tmp!=7)&&(cnt3==0))
     {
         obs_p1 = tmp;
         obs_p2 = tmp;
         cnt3=1;
     }
     else if ((tmp!=7)&&(tmp!=obs_p2))
     {
     obs_p1 = obs_p2;
     obs_p2 = tmp;
     }

    // cnt2 = cnt2+1;

     printf("ges_type1 is %d\n", obs_p1);
     printf("likelihood1 value is %f\n", lik1);
     printf("ges_type2 is %d\n", value2);
     printf("likelihood2 value is %f\n", lik2);
     printf("ges_type3 is %d\n", value3);
     printf("likelihood3 value is %f\n", lik3);

     cnt = 0;


      ges.gesture1 = value1;
      ges.gesture2 = value2;
      ges.gesture3 = value3;
      pub.publish(ges);


     }

}
//printf("cnt = %d\n",cnt);

//comment out here


// data processing

}
// %EndTag(CALLBACK)%

int main(int argc, char **argv)
{
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line. For programmatic
   * remappings you can use a different version of init() which takes remappings
   * directly, but for most command-line programs, passing argc and argv is the easiest
   * way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
    ros::init(argc, argv, "talker");
    Hmm hmm(0,0);

   // hmm.init();


    const char * argvv [] = {"" /* name of program, not relevant */, "--silent"};
     octave_main (2, (char **) argvv, true /* embedded */);

   //  ros::init(argc, argv, "listener");

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle n;

  /**
   * The subscribe() call is how you tell ROS that you want to receive messages
   * on a given topic.  This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing.  Messages are passed to a callback function, here
   * called chatterCallback.  subscribe() returns a Subscriber object that you
   * must hold on to until you want to unsubscribe.  When all copies of the Subscriber
   * object go out of scope, this callback will automatically be unsubscribed from
   * this topic.
   *
   * The second parameter to the subscribe() function is the size of the message
   * queue.  If messages are arriving faster than they are being processed, this
   * is the number of messages that will be buffered up before beginning to throw
   * away the oldest ones.
   */
// %Tag(SUBSCRIBER)%
  //ros::Subscriber sub = n.subscribe("Langles", 4, hmm.chatterCallback);
  ros::Subscriber sub = n.subscribe("Langles", 40, &Hmm::chatterCallback, &hmm);
// %EndTag(SUBSCRIBER)%


  /**
   * ros::spin() will enter a loop, pumping callbacks.  With this version, all
   * callbacks will be called from within this thread (the main one).  ros::spin()
   * will exit when Ctrl-C is pressed, or the node is shutdown by the master.
   */
// %Tag(SPIN)%
  ros::spin();
// %EndTag(SPIN)%

  return 0;
}
// %EndTag(FULLTEXT)%
