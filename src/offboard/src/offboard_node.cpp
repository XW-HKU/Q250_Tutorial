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
#include <Eigen/Dense>
#include <Eigen/Core>
#include <tf2/LinearMath/Quaternion.h>
#include <data.h>
#include <math_by_gene.hpp>


#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

enum traj_mode_t  {HOVER , TRAJ_1 , TRAJ_2 , TRAJ_3 , TRAJ_4};
traj_mode_t traj_mode  = TRAJ_1;
#define TAKEOFF_TIME (3*50)
#define HOVER_TIME (7*50)
#define PRIOR_TIME (TAKEOFF_TIME + HOVER_TIME)

geometry_msgs::PoseStamped current_local_pos;  //!< Current local position in ENU

mavros_msgs::State current_state;
void state_cb(const mavros_msgs::State::ConstPtr& msg){
    current_state = *msg;
}

void local_cb(const geometry_msgs::PoseStamped::ConstPtr &msg)
{
    //current_local_pos = ftf::to_eigen(msg->pose.position);
    current_local_pos = *msg;
}

int main(int argc, char **argv)
{
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

    geometry_msgs::PoseStamped last_pose;
    gene_math_xyz_copy_to_xyz(&current_local_pos.pose.position , &last_pose.pose.position);
    gene_math_wxyz_copy_to_wxyz(&current_local_pos.pose.orientation , &last_pose.pose.orientation);    

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

//*********  test **************//
    float test_f = 0.1;
    float tmp = 0;
    float yaw = 0;
    tf2::Quaternion q_tar;

// ************ read text test *********//
    int data_row = 1101;
    int data_col = 18;
    int traj_cnt = 0;
    int wait_cnt = 0;
    extern const float traj_data[1101][18];

    while(ros::ok()){
        if((current_state.mode == "OFFBOARD") && current_state.armed)
        {   
            if (wait_cnt < 50 * 5)
            {
                wait_cnt ++;
                pose.pose.position.x = 0.0f;
                pose.pose.position.y = 0.0f;
                pose.pose.position.z = 0.0f;
            } 
            else
            {
                switch (traj_mode)
                {
                    case HOVER:
                        if (traj_cnt < PRIOR_TIME)
                        {
                            traj_cnt ++;
                        }

                        gene_math_v3_copy_to_xyz(&traj_data[traj_cnt][0] , &pose.pose.position);
                        gene_math_wxyz_copy_to_wxyz(&last_pose.pose.orientation , &pose.pose.orientation);
                        break;

                    case TRAJ_1:
                        traj_cnt ++;
                        if (traj_cnt >= data_row)
                        {
                            traj_cnt = PRIOR_TIME;
                        }

                        gene_math_v3_copy_to_xyz(&traj_data[traj_cnt][0] , &pose.pose.position);
                        gene_math_v4_copy_to_wxyz(&traj_data[traj_cnt][14] , &pose.pose.orientation);
                        break;

                    case TRAJ_2:
                        traj_cnt ++;
                        if (traj_cnt < PRIOR_TIME)
                        {
                            gene_math_v3_copy_to_xyz(&traj_data[traj_cnt][0] , &pose.pose.position);
                            gene_math_wxyz_copy_to_wxyz(&last_pose.pose.orientation , &pose.pose.orientation);
                        }
                        else if (traj_cnt < PRIOR_TIME + 5 * 50)
                        {
                            gene_math_v3_copy_to_xyz(&traj_data[PRIOR_TIME][0] , &pose.pose.position);

                            pose.pose.orientation.w = 1.0f;
                            pose.pose.orientation.x = 0.0f;
                            pose.pose.orientation.y = 0.0f;
                            pose.pose.orientation.z = 0.0f;
                        }
                        else if (traj_cnt < PRIOR_TIME + 5 * 50 + HOVER_TIME)
                        {
                            gene_math_v3_copy_to_xyz(&traj_data[PRIOR_TIME][0] , &pose.pose.position);
                            pose.pose.position.x += traj_data[traj_cnt - PRIOR_TIME - 5 * 50][2];

                            pose.pose.orientation.w = 1.0f;
                            pose.pose.orientation.x = 0.0f;
                            pose.pose.orientation.y = 0.0f;
                            pose.pose.orientation.z = 0.0f;
                        }
                        else
                        {
                            gene_math_v3_copy_to_xyz(&traj_data[PRIOR_TIME][0] , &pose.pose.position);
                            pose.pose.position.x += traj_data[PRIOR_TIME][2];

                            pose.pose.orientation.w = 1.0f;
                            pose.pose.orientation.x = 0.0f;
                            pose.pose.orientation.y = 0.0f;
                            pose.pose.orientation.z = 0.0f;
                        }   
                        
                        break;

                    default:
                        break;

                }
            }
        

            ROS_INFO("Switch into OFFBOARD mode!");

            // ROS_INFO("Continued Time: %f", offb_time);

            ROS_INFO("Traj_cnt: %d ; Target Positon: %f, %f , %f", traj_cnt , pose.pose.position.x , pose.pose.position.y , pose.pose.position.z);
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

            // tcnt = 250;

            //last_pose.pose.position.x = pose.pose.position.x;
            //last_pose.pose.position.y = pose.pose.position.y;
            //last_pose.pose.position.z = pose.pose.position.z;

            // memcpy(&(last_pose.pose),&(pose.pose), sizeof(pose.pose));

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