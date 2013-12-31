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

/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
// %Tag(CALLBACK)%


class Hmm
{
public:
  //TeleopNaoNi();
     void chatterCallback(const msg_kinect::esangles);
     octave_value_list foutput;
     //octave_value finput;
     //Matrix data;
     float gesture;
     int cnt;
     //float dataset[10];
};




void Hmm::chatterCallback(const msg_kinect::esangles msg)
{

if (msg.leroll!= 0)
     //continue;
{//comment here
        if (cnt<10)
      {
      // dataset[cnt] = angles;
         FILE * pFile;
         pFile = fopen("/home/ye/projects/hmm/hmm/hmmtest.txt","a");

         int status = fprintf(pFile, "%f \t", msg.leroll);
         if (status<0) printf("writing error fuck!!");

         status = fprintf(pFile, "%f \t", msg.leyaw);
         if (status<0) printf("writing error fuck!!");

         status = fprintf(pFile, "%f \t", msg.lsroll);
         if (status<0) printf("writing error fuck!!");

         status = fprintf(pFile, "%f \t", msg.lspitch);
         if (status<0) printf("writing error fuck!!");


         fputs("\n",pFile);

		 fclose(pFile);
       // printf("91 Line!!\n");
        cnt =cnt+1;

      }
      else
      {



          //finput2 = cnt;

         foutput = feval("testinghmm_4doctave");





   //  thres[0] = f_ret1(0).double_value();
     gesture = foutput(0).double_value();
     printf("gesture is %f\n", gesture);



      cnt = 0;
   //printf("114 Line!!\n");

     }




}//comment out here


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
    Hmm hmm;
    const char * argvv [] = {"" /* name of program, not relevant */, "--silent"};
     octave_main (2, (char **) argvv, true /* embedded */);

     ros::init(argc, argv, "listener");

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
  ros::Subscriber sub = n.subscribe("Langles", 4, &Hmm::chatterCallback, &hmm);
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
