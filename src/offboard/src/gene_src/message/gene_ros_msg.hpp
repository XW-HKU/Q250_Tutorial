#ifndef  GENE_ROS_MSG_H
#define  GENE_ROS_MSG_H

#include "../math/gene_math.hpp"
#include "../control/gene_control.hpp"
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TwistStamped.h>

#define OFFBORAD_RUN_RATE 50

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

void gene_math_copy_v3f_to_point_msg(const Vector3f &v_src , geometry_msgs::Point_<std::allocator<void> > &point_msg);

void gene_math_copy_v4f_to_quat_msg(const Quaternionf &q_src , geometry_msgs::Quaternion_<std::allocator<void> > &quat_msg);

void gene_math_copy_point_msg_to_v3f(Vector3f &v_des , const geometry_msgs::Point_<std::allocator<void> > &point_msg);


void gene_math_copy_quat_msg_to_v4f(Quaternionf &q_des , const geometry_msgs::Quaternion_<std::allocator<void> > &quat_msg);

void gene_math_copy_vector_msg_to_v3f(Vector3f &v_des , const geometry_msgs::Vector3_<std::allocator<void> > &vector_msg);

void gene_feedback_msg_receive(feedback_t &fb,
                               geometry_msgs::PoseStamped  &local_pose,
                               geometry_msgs::TwistStamped &local_twist,
                               geometry_msgs::TwistStamped &body_twist);


#endif