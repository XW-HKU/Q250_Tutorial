#ifndef  MATH_BY_GENE_H
#define  MATH_BY_GENE_H

#include <geometry_msgs/PoseStamped.h>

typedef float v3_t[3];
typedef float q_t[4];
typedef double v3_64t[3];

struct vector_xyz_64t
{
    double x;
    double y;
    double z;
};

struct vector_wxyz_64t
{
    double w;
    double x;
    double y;
    double z;
};

void gene_math_v3_copy_to_xyz(const v3_t v_in , geometry_msgs::Pose_<std::allocator<void> >::_position_type *v_out);
void gene_math_v4_copy_to_wxyz(const q_t q_in , geometry_msgs::Pose_<std::allocator<void> >::_orientation_type *q_out);
void gene_math_xyz_copy_to_xyz(geometry_msgs::Pose_<std::allocator<void> >::_position_type *v_in , geometry_msgs::Pose_<std::allocator<void> >::_position_type *v_out);
void gene_math_wxyz_copy_to_wxyz(geometry_msgs::Pose_<std::allocator<void> >::_orientation_type *v_in , geometry_msgs::Pose_<std::allocator<void> >::_orientation_type *v_out);



#endif