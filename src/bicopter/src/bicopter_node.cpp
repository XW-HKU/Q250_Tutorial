#include "ros/ros.h"
#include "tf/transform_broadcaster.h"
#include "tf/transform_listener.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/PoseStamped.h"
#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

double x_drone,y_drone,z_drone;

void OdomCallback(const nav_msgs::Odometry::ConstPtr& msg){
  double x_cam = msg->pose.pose.position.x;
  double y_cam = msg->pose.pose.position.y;
  double z_cam = msg->pose.pose.position.z;
  double x_orcam = msg->pose.pose.orientation.x;
  double y_orcam = msg->pose.pose.orientation.y;
  double z_orcam = msg->pose.pose.orientation.z;
  double w_orcam = msg->pose.pose.orientation.w;

  static tf::TransformBroadcaster br;
  tf::Transform Tic;
  Tic.setOrigin(tf::Vector3(x_cam,y_cam,z_cam));
  Tic.setRotation(tf::Quaternion(x_orcam,y_orcam,z_orcam,w_orcam));

  tf::Transform Tcb;
  Tcb.setOrigin(tf::Vector3(-0.0285,-0.009,-0.047));
  Tcb.setBasis(tf::Matrix3x3(1,0,0,0,-1,0,0,0,-1));
    
  tf::Transform drone_pose = Tic*Tcb;
  // tf::Quaternion q = drone_pose.getRotation();
  tf::Vector3 v = drone_pose.getOrigin();
  x_drone = v.getX();
  y_drone = v.getY();
  z_drone = v.getZ();
  // double x_ordrone = q.x
  // double y_ordrone = q.y
  // double z_ordrone = q.z
  // double w_ordrone = q.w 
  br.sendTransform(tf::StampedTransform(drone_pose,ros::Time::now(),"camera_odom_frame","drone_pose")); 

}
int main(int argc, char **argv) {
  ros::init(argc, argv, "bicopter_node");
  ros::NodeHandle n;
  tf::TransformBroadcaster br;
  ros::Rate loop_rate(240.0);
  ros::Subscriber sub = n.subscribe("camera/odom/sample",10, OdomCallback);
  ros::Publisher pub = n.advertise<geometry_msgs::PoseStamped>("drone_pose",1000);
  int count = 0;
  while (ros::ok())
  {
    geometry_msgs::PoseStamped PoseStamped;
    PoseStamped.pose.position.x = x_drone;
    PoseStamped.pose.position.y = y_drone;
    PoseStamped.pose.position.z = z_drone;  
    pub.publish(PoseStamped);
    ros::spinOnce();
    loop_rate.sleep();
    ++count;

  }
  ros::spin();
  return 0;
}


