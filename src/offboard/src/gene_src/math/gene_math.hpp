#ifndef  GENE_MATH_H
#define  GENE_MATH_H

#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <Eigen/Dense>

using namespace Eigen;

typedef float v3_t[3];
typedef float q_t[4];


void gene_math_copy_v3f_to_point_msg(const Vector3f &v_src , geometry_msgs::Point_<std::allocator<void> > &point_msg);

void gene_math_copy_v4f_to_quat_msg(const Quaternionf &q_src , geometry_msgs::Quaternion_<std::allocator<void> > &quat_msg);

void gene_math_copy_point_msg_to_v3f(Vector3f &v_des , const geometry_msgs::Point_<std::allocator<void> > &point_msg);

void gene_math_copy_quat_msg_to_v4f(Quaternionf &q_des , const geometry_msgs::Quaternion_<std::allocator<void> > &quat_msg);

void gene_math_copy_vector_msg_to_v3f(Vector3f &v_des , const geometry_msgs::Vector3_<std::allocator<void> > &vector_msg);

#endif