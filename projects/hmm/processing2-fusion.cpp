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
     octave_value_list foutput1, foutput2, foutput3;
     octave_value finput;
     Matrix data, temp;
    // float gesture;
     int cnt;
     Hmm(int,int);
     int cnt2, slide_start;
     int value1, value2, value3;
     float lik1, lik2, lik3;
     int dtw1, dtw2, dtw3;
     float dis1, dis2, dis3;
     clock_t start, end;
     int valuel, valuel2;
     float c1, c2;
     int ges_f1, ges_f2;

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
         data = Matrix(20,4);
         temp = Matrix(20,4);
         slide_start = 0;
         pub = n.advertise<msg_kinect::esangles>("talker", 1000);

     }
//void Hmm::init(){cnt=0; data = Matrix(10,4);}
void Hmm::chatterCallback(const msg_kinect::esangles& msg)
{
   // FILE *pFile;

if (msg.leroll!= 0)
     //continue;
{//comment here
        if (cnt<20)
      {

      // dataset[cnt] = angles;
       if (slide_start==0)
       {
       data(cnt,0) = float(msg.leroll);
       data(cnt,1) = float(msg.leyaw);
       data(cnt,2) = float (msg.lsroll);
       data(cnt,3) = float (msg.lspitch);
       cnt = cnt + 1 ;

       }
       else
       {
       //shifting first then adding new data
      /* for (int ii=0;ii<10;ii++)
       {
        temp(ii,0) = data(ii+5, 0);
        temp(ii,1) = data(ii+5, 1);
        temp(ii,2) = data(ii+5, 2);
        temp(ii,3) = data(ii+5, 3);
       }
       //sliding

       for (int ii=0;ii<10;ii++)
       {
        data(ii,0) = temp(ii, 0);
        data(ii,1) = temp(ii, 1);
        data(ii,2) = temp(ii, 2);
        data(ii,3) = temp(ii, 3);
       }*/
     //  data = temp;
       //login new data
       data(cnt,0) = float(msg.leroll);
       data(cnt,1) = float(msg.leyaw);
       data(cnt,2) = float (msg.lsroll);
       data(cnt,3) = float (msg.lspitch);
       cnt = cnt + 1 ;


       }
        /* pFile = fopen("/home/ye/projects/hmm/hmm/hmmtest.txt","a");

         int status = fprintf(pFile, "%f \t", msg.leroll);
         if (status<0) printf("writing error fuck!!");

         status = fprintf(pFile, "%f \t", msg.leyaw);
         if (status<0) printf("writing error fuck!!");

         status = fprintf(pFile, "%f \t", msg.lsroll);
         if (status<0) printf("writing error fuck!!");

         status = fprintf(pFile, "%f \t", msg.lspitch);
         if (status<0) printf("writing error fuck!!");


         fputs("\n",pFile);

		 fclose(pFile);*/





      }
      else
      {
       start = clock();
   //    printf("time is %f\n", start);

         finput= data;
    //     finput = data;
          //finput2 = cnt;
//Major Vote
    if (cnt2==0)
    {

     foutput1 = feval("hmm_dtw_fusion", finput);
     value1  = foutput1(0).double_value();
     lik1 = foutput1(1).double_value();
     dtw1  = foutput1(2).double_value();
     dis1 = foutput1(3).double_value();
      c1 = foutput1(4).double_value();
      ges_f1 = foutput1(5).double_value();
      c2 = foutput1(6).double_value();
      ges_f2 = foutput1(7).double_value();

     printf("fusion decision 1 is %d\n", ges_f1);
     printf("confidence value 1 is %f\n", c1);
     printf("fusion decision 2 is %d\n", ges_f2);
     printf("confidence value 2 is %f\n", c2);

     cnt2 = cnt2+1;
    }
     else if(cnt2 == 1)
   //  printf("gesture is %d\n", gesture);
    // printf("likelihood value is %f\n", value);
  //   printf("variance value is %f\n", var);
     {
     foutput2 = feval("hmm_dtw_fusion", finput);
     value2  = foutput2(0).double_value();
     lik2 = foutput2(1).double_value();
     dtw2  = foutput2(2).double_value();
     dis2 = foutput2(3).double_value();
     c1 = foutput2(4).double_value();
      ges_f1 = foutput2(5).double_value();
      c2 = foutput2(6).double_value();
      ges_f2 = foutput2(7).double_value();

     printf("fusion decision 1 is %d\n", ges_f1);
     printf("confidence value 1 is %f\n", c1);
     printf("fusion decision 2 is %d\n", ges_f2);
     printf("confidence value 2 is %f\n", c2);

     cnt2 = cnt2 + 1;
      }
      else
      {
      foutput3 = feval("hmm_dtw_fusion", finput);
      value3  = foutput3(0).double_value();
      lik3 = foutput3(1).double_value();
      dtw3  = foutput3(2).double_value();
      dis3 = foutput3(3).double_value();
      c1 = foutput3(4).double_value();
      ges_f1 = foutput3(5).double_value();
      c2 = foutput3(6).double_value();
      ges_f2 = foutput3(7).double_value();

     printf("fusion decision 1 is %d\n", ges_f1);
     printf("confidence value 1 is %f\n", c1);
     printf("fusion decision 2 is %d\n", ges_f2);
     printf("confidence value 2 is %f\n", c2);

     cnt2 = 0;

      }


      if ((value1==value2) || (value1==value3))
      {
      printf("gesture is %d\n", value1);
      printf("likelihood value is %f\n", lik1);
      valuel = value1;
      }
      else if (value2==value3)
      {
      printf("gesture is %d\n", value2);
      printf("likelihood value is %f\n", lik2);
      valuel = value2;
      }

      else
      {
      printf("NO MAJOR VOTING, gesture is %d\n", 0);
      valuel= 0;
   //   printf("no majority voting\n");
      }

      /////////////////dtw decision///////////////////////////////

     if ((dtw1==dtw2) || (dtw1==dtw3))
      {
      printf("gestureDTW is %d\n", dtw1);
      printf("dtw distance is %f\n", dis1);
      valuel2 = dtw1;
      }
      else if (dtw2==dtw3)
      {
      printf("gestureDTW is %d\n", dtw2);
      printf("likelihood value is %f\n", dis2);
      valuel2 = dtw2;
      }

      else
      {
      printf("NO MAJOR VOTING DTW, gestureDTW is %d\n", 0);
      valuel2= 0;
   //   printf("no majority voting\n");
      }

     cnt = 0;
     slide_start = 1;
     end = clock();
    // printf("ENdtime is %f\n", end);
     //float timeused = (end-start)/CLOCKS_PER_SEC;
    // printf("Time used is %f\n", timeused);

      ges.gesture = valuel;
      ges.gesture2 = valuel2;
      ges.ges_f1 = ges_f1;
      ges.ges_f2 = ges_f2;
      pub.publish(ges);


     }


//printf("cnt = %d\n",cnt);

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
