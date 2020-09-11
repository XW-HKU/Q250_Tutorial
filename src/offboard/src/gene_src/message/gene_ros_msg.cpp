#include "gene_ros_msg.hpp"

// @brief: copy Vertor3f to double xyz msg
void gene_math_v3f_copy_to_point_msg(const Vector3f v_in , geometry_msgs::Point_<std::allocator<void> > *point_msg)
{
    point_msg->x = v_in(0);
    point_msg->y = v_in(1);
    point_msg->z = v_in(2);
}

// @brief: copy Vertor4f to a double wxyz msg
void gene_math_v4f_copy_to_quat_msg(const Quaternionf q_in , geometry_msgs::Quaternion_<std::allocator<void> > *quat_msg)
{
    quat_msg->w = q_in.w();
    quat_msg->x = q_in.x();
    quat_msg->y = q_in.y();
    quat_msg->z = q_in.z();
}

// // @brief: copy a xyz msg to a double xyz msg
// void gene_math_xyz_copy_to_xyz(geometry_msgs::Pose_<std::allocator<void> >::_position_type *v_in , geometry_msgs::Pose_<std::allocator<void> > *v_out)
// {
//     v_out->x = v_in->x;
//     v_out->y = v_in->y;
//     v_out->z = v_in->z;
// }

// // @brief: copy a wxyz msg to a double wxyz msg
// void gene_math_wxyz_copy_to_wxyz(geometry_msgs::Pose_<std::allocator<void> >::_orientation_type *v_in , geometry_msgs::Pose_<std::allocator<void> > *v_out)
// {
//     v_out->w = v_in->w;
//     v_out->x = v_in->x;
//     v_out->y = v_in->y;
//     v_out->z = v_in->z;
// }
