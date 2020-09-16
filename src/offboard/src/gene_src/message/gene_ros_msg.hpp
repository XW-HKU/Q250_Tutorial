#ifndef  GENE_ROS_MSG_H
#define  GENE_ROS_MSG_H


#include "../math/gene_math.hpp"
#include "../trajectory/gene_trajectory_generation.hpp"


#define LOG_NUM           33

struct feedback_t
{
    Vector3f                                           pos;            // local position,               unit: m
    Vector3f                                           vel;            // local velocity,               unit: m/s
    Vector3f                                           vel_body;       // body velocity,                unit: m/s
    Vector3f                                           acc;            // local acceleration,           unit: m/s^2
    Vector3f                                           omega;          // body angular rate,            unit: rad/s
    Vector3f                                           ang_acc;        // body angular acceleration,    unit: rad/s^2
    Vector3f                                           euler;          // Euler angle,                  unit: rad
    Quaternionf                                        q_eb;           // quaternion
    Matrix3f                                           R_eb;           // rotation matrix
};

typedef std::vector<Eigen::Matrix<float, 1, LOG_NUM>> log_t;



void gene_feedback_msg_receive(feedback_t &fb,
                               geometry_msgs::PoseStamped  &local_pose,
                               geometry_msgs::TwistStamped &local_twist,
                               geometry_msgs::TwistStamped &body_twist);

void gene_log_save(log_t &log_data , float time_stamp, feedback_t &fb, traj_t &traj);

#endif