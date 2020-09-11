#ifndef  GENE_ROS_MSG_H
#define  GENE_ROS_MSG_H

#include "../math/gene_math.hpp"
#include <geometry_msgs/PoseStamped.h>

#define OFFBORAD_RUN_RATE 50

void gene_math_v3f_copy_to_point_msg(const Vector3f v_in , geometry_msgs::Point_<std::allocator<void> > *point_msg);

void gene_math_v4f_copy_to_quat_msg(const Quaternionf q_in , geometry_msgs::Quaternion_<std::allocator<void> > *quat_msg);

// void gene_math_xyz_copy_to_xyz(geometry_msgs::Pose_<std::allocator<void> >::_position_type *v_in,
//                                     geometry_msgs::Pose_<std::allocator<void> >::_position_type *v_out);

// void gene_math_wxyz_copy_to_wxyz(geometry_msgs::Pose_<std::allocator<void> >::_orientation_type *v_in,
//                                     geometry_msgs::Pose_<std::allocator<void> >::_orientation_type *v_out);


#endif