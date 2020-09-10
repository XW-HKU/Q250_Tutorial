#include "math_by_gene.hpp"

// @brief: copy a 3-d float vector to a double xyz msg
void gene_math_v3_copy_to_xyz(const v3_t v_in , geometry_msgs::Pose_<std::allocator<void> >::_position_type *v_out)
{
    v_out->x = v_in[0];
    v_out->y = v_in[1];
    v_out->z = v_in[2];
}

// @brief: copy a 4-d float vector to a double wxyz msg
void gene_math_v4_copy_to_wxyz(const q_t q_in , geometry_msgs::Pose_<std::allocator<void> >::_orientation_type *q_out)
{
    q_out->w = q_in[0];
    q_out->x = q_in[1];
    q_out->y = q_in[2];
    q_out->z = q_in[3];
}

// @brief: copy a xyz msg to a double xyz msg
void gene_math_xyz_copy_to_xyz(geometry_msgs::Pose_<std::allocator<void> >::_position_type *v_in , geometry_msgs::Pose_<std::allocator<void> >::_position_type *v_out)
{
    v_out->x = v_in->x;
    v_out->y = v_in->y;
    v_out->z = v_in->z;
}

// @brief: copy a wxyz msg to a double wxyz msg
void gene_math_wxyz_copy_to_wxyz(geometry_msgs::Pose_<std::allocator<void> >::_orientation_type *v_in , geometry_msgs::Pose_<std::allocator<void> >::_orientation_type *v_out)
{
    v_out->w = v_in->w;
    v_out->x = v_in->x;
    v_out->y = v_in->y;
    v_out->z = v_in->z;
}
