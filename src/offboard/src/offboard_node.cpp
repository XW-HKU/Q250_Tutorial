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
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <tf2/LinearMath/Quaternion.h>
#include <data.h>
#include <gene_src.hpp>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;
extern const traj_data_t traj_data;

geometry_msgs::PoseStamped current_local_pos;  //!< Current local position in ENU

mavros_msgs::State current_state;
void state_cb(const mavros_msgs::State::ConstPtr& msg){
    current_state = *msg;
}

void local_cb(const geometry_msgs::PoseStamped::ConstPtr &msg)
{
    current_local_pos = *msg;
}

int main(int argc, char **argv)
{
    // ************ read data file *********//
    traj_t traj;
    traj.mode = TRAJ_1;
    // ************************************//


    ros::init(argc, argv, "offb_node");
    ros::NodeHandle nh;

    ros::Subscriber cur_leader_pos_sub = nh.subscribe<geometry_msgs::PoseStamped>
            ("mavros/local_position/pose", 10, local_cb);
    ros::Subscriber state_sub = nh.subscribe<mavros_msgs::State>
            ("mavros/state", 10, state_cb);
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

    ros::Time last_request = ros::Time::now();
    double offb_time = 0;


    while(ros::ok()){
        if((current_state.mode == "OFFBOARD") && current_state.armed)
        {   

            gene_offline_traj_generate(&traj, traj_data, &(pose.pose));
        

            ROS_INFO("Switch into OFFBOARD mode!");

            // ROS_INFO("Continued Time: %f", offb_time);

            ROS_INFO("Traj_cnt: %d ; Target Positon: %f, %f , %f; Target Quat: %f, %f , %f , %f", traj.read_cnt , pose.pose.position.x , pose.pose.position.y , pose.pose.position.z ,
                                                        pose.pose.orientation.w , pose.pose.orientation.x , pose.pose.orientation.y , pose.pose.orientation.z);
        }
        else
        {
            pose.pose.position.x = current_local_pos.pose.position.x;
            pose.pose.position.y = current_local_pos.pose.position.y;
            pose.pose.position.z = current_local_pos.pose.position.z;

            pose.pose.orientation.w = current_local_pos.pose.orientation.w;
            pose.pose.orientation.x = current_local_pos.pose.orientation.x;
            pose.pose.orientation.y = current_local_pos.pose.orientation.y;
            pose.pose.orientation.z = current_local_pos.pose.orientation.z;

            last_request = ros::Time::now();
        }



        // tmp += 2.0f * M_PI * test_f * 0.05;
        // if (tmp > 2.0f * M_PI)
        // {
        //     tmp -= 2.0f * M_PI;
        // }
        // yaw = M_PI * sin(tmp);

        
        // q_tar.setRPY( 0.0f, -0.0f, yaw);  // Create this quaternion from roll/pitch/yaw (in radians)

        // pose.pose.orientation.x = q_tar.x();
        // pose.pose.orientation.y = q_tar.y();
        // pose.pose.orientation.z = q_tar.z();
        // pose.pose.orientation.w = q_tar.w();

        // ROS_INFO_STREAM(q_tar);

        // Eigen::Matrix3d R;
        // R<<1,0,0,0,1,0,0,0,1;
        // std::cout<<q_tar.w()<<", "<<q_tar.x()<<", "<<q_tar.y()<<", "<<q_tar.z()<<"\n";

        // std::cout<<temp<<"\n";
        // std::cout<<number<<", "<<word<<", "<<real<<", "<<letter<<"\n";


        //****************** set tar pose and quat ******************//
        // cnt ++;
        // if (cnt >= data_row)
        // {
        //     cnt = 250;
        // }

        // pose.pose.position.x = traj_data[cnt][0];
        // pose.pose.position.y = traj_data[cnt][1];
        // pose.pose.position.z = traj_data[cnt][2];

        // pose.pose.orientation.w = traj_data[cnt][14];
        // pose.pose.orientation.x = traj_data[cnt][15];
        // pose.pose.orientation.y = traj_data[cnt][16];
        // pose.pose.orientation.z = traj_data[cnt][17];

        // std::cout<<pose.pose.position.x<<", "<<pose.pose.position.y<<", "<<pose.pose.position.z<<", "<<pose.pose.orientation.w
        //             <<", "<<pose.pose.orientation.x<<", "<<pose.pose.orientation.y<<", "<<pose.pose.orientation.z<<"\n";

        // std::cout<<cnt<<": "<<pose.pose.position.x<<", "<<pose.pose.position.y<<"\n";
 
        local_pos_pub.publish(pose);

        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}