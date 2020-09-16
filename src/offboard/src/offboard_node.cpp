/**
 * @file offb_node.cpp
 * @brief Offboard control example node, written with MAVROS version 0.19.x, PX4 Pro Flight
 * Stack and tested in Gazebo SITL
 */

#include <ros/ros.h>
#include <omp.h>
#include <math.h>
#include <unistd.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <tf2/LinearMath/Quaternion.h>
#include <data.h>
#include <gene_src.hpp>
#include <iostream>
#include <iomanip>
#include <fstream>
// #include "matplotlibcpp.h"

// namespace plt = matplotlibcpp;

using namespace std;
extern const traj_data_t traj_data;

mavros_msgs::State current_state;
geometry_msgs::PoseStamped current_local_pose;     //!< Current local pose in ENU
geometry_msgs::TwistStamped current_local_twist;   //!< Current local twist in ENU
geometry_msgs::TwistStamped current_body_twist;    //!< Current local twist in body

traj_t      trajectory;
feedback_t  feedback;
log_t       log_data;


void state_cb(const mavros_msgs::State::ConstPtr& msg){
    current_state = *msg;
}

void local_pose_cb(const geometry_msgs::PoseStamped::ConstPtr &msg)
{
    current_local_pose = *msg;
}

void local_twist_cb(const geometry_msgs::TwistStamped::ConstPtr &msg)
{
    current_local_twist = *msg;
}

void body_twist_cb(const geometry_msgs::TwistStamped::ConstPtr &msg)
{
    current_body_twist = *msg;
}

int main(int argc, char **argv)
{
    // ************ Initailation *********//
    trajectory.mode = TRAJ_1;
    float ros_time_stamp;
    // ************************************//


    ros::init(argc, argv, "offb_node");
    ros::NodeHandle nh;

    ros::Subscriber state_sub = nh.subscribe<mavros_msgs::State>
            ("mavros/state", 10, state_cb);
    ros::Subscriber cur_local_pos_sub = nh.subscribe<geometry_msgs::PoseStamped>
            ("mavros/local_position/pose", 10, local_pose_cb);
    ros::Subscriber cur_local_twist_sub = nh.subscribe<geometry_msgs::TwistStamped>
            ("mavros/local_position/velocity_local", 10, local_twist_cb);
    ros::Subscriber cur_body_twist_sub = nh.subscribe<geometry_msgs::TwistStamped>
            ("mavros/local_position/velocity_body", 10, body_twist_cb);
    

    ros::Publisher local_pos_pub = nh.advertise<geometry_msgs::PoseStamped>
            ("mavros/setpoint_position/local", 10);
    ros::ServiceClient arming_client = nh.serviceClient<mavros_msgs::CommandBool>
            ("mavros/cmd/arming");
    ros::ServiceClient set_mode_client = nh.serviceClient<mavros_msgs::SetMode>
            ("mavros/set_mode");

    //the setpoint publishing rate MUST be faster than 2Hz
    ros::Rate rate(50.0);

    // wait for FCU connection
    while(ros::ok() && !current_state.connected){
        ros::spinOnce();
        rate.sleep();
    }

    geometry_msgs::PoseStamped pose;
   
    //send a few setpoints before starting
    for(int i = 100; ros::ok() && i > 0; --i){
        local_pos_pub.publish(pose);
        ros::spinOnce();
        rate.sleep();
    }

    mavros_msgs::SetMode offb_set_mode;
    offb_set_mode.request.custom_mode = "OFFBOARD";

    mavros_msgs::CommandBool arm_cmd;
    arm_cmd.request.value = true;

    ros::Time time_begin = ros::Time::now();
    ros::Time time_current;
    double offb_time = 0;


    while(ros::ok()){
        if((current_state.mode == "OFFBOARD") && current_state.armed)
        {   
            /* 1. receive feedback data from ros msg */
            gene_feedback_msg_receive(feedback,
                                            current_local_pose,
                                            current_local_twist,
                                            current_body_twist);

            /* 2. plan a trajectory */
            gene_offline_traj_generate(trajectory, traj_data, pose.pose);
        

            Vector3f vec_test;
            vec_test = feedback.q_eb.normalized().toRotationMatrix() * feedback.vel_body;

            ROS_INFO("Switch into OFFBOARD mode!");

            // ROS_INFO("Continued Time: %f", offb_time);

            // ROS_INFO("Traj_cnt: %d ; Target Positon: %f, %f , %f; Target Quat: %f, %f , %f , %f", trajectory.read_cnt , pose.pose.position.x , pose.pose.position.y , pose.pose.position.z ,
            //                                             pose.pose.orientation.w , pose.pose.orientation.x , pose.pose.orientation.y , pose.pose.orientation.z);
        
            // ROS_INFO("Traj_cnt: %d ;\n Target Positon: %f, %f , %f ;\n Fusion Positon: %f, %f , %f", 
            //             trajectory.read_cnt , pose.pose.position.x , pose.pose.position.y , pose.pose.position.z,
            //             feedback.pos(0) , feedback.pos(1) , feedback.pos(2));

            // ROS_INFO("Traj_cnt: %d ;\n Target quat: %f, %f , %f , %f;\n Fusion quat: %f, %f , %f , %f", 
            //             trajectory.read_cnt , pose.pose.orientation.w , pose.pose.orientation.x , pose.pose.orientation.y , pose.pose.orientation.z,
            //             feedback.q_eb.w() , feedback.q_eb.x() , feedback.q_eb.y() , feedback.q_eb.z());

            // ROS_INFO("Traj_cnt: %d ;\n local vel: %f, %f , %f ;\n body vel: %f, %f , %f ;\n test vel: %f, %f , %f", 
            //             trajectory.read_cnt , feedback.vel(0) , feedback.vel(1) , feedback.vel(2),
            //             feedback.vel_body(0) , feedback.vel_body(1) , feedback.vel_body(2),
            //             vec_test(0) , vec_test(1) , vec_test(2));

            // ROS_INFO("Traj_cnt: %d ;\n Target quat: %f, %f , %f , %f",
            //             trajectory.read_cnt , trajectory.q.w() , trajectory.q.x() , trajectory.q.y() , trajectory.q.z());
            

            // cout << "Rotation: " << R <<endl;
        }
        else
        {
            pose.pose.position.x = current_local_pose.pose.position.x;
            pose.pose.position.y = current_local_pose.pose.position.y;
            pose.pose.position.z = current_local_pose.pose.position.z;

            pose.pose.orientation.w = current_local_pose.pose.orientation.w;
            pose.pose.orientation.x = current_local_pose.pose.orientation.x;
            pose.pose.orientation.y = current_local_pose.pose.orientation.y;
            pose.pose.orientation.z = current_local_pose.pose.orientation.z;

            
        }

        local_pos_pub.publish(pose);

        time_current = ros::Time::now();
        ros_time_stamp = (time_current - time_begin).toSec();

        gene_log_save(log_data, ros_time_stamp, feedback, trajectory);

        ros::spinOnce();
        rate.sleep();
    }

    std::ofstream log_file("./src/offboard/log/log_data.txt");
    std::ostream_iterator<Eigen::Matrix<float, 1, LOG_NUM>> log_iterator(log_file, "\n");
    std::copy(log_data.begin(), log_data.end(), log_iterator);


    return 0;
}