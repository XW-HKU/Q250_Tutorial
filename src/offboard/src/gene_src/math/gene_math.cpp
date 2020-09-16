#include "gene_math.hpp"

// @brief: copy Vertor3f to double xyz point msg
void gene_math_copy_v3f_to_point_msg(const Vector3f &v_src , geometry_msgs::Point_<std::allocator<void> > &point_msg)
{
    point_msg.x = v_src(0);
    point_msg.y = v_src(1);
    point_msg.z = v_src(2);
}

// @brief: copy Vertor4f to double wxyz msg
void gene_math_copy_v4f_to_quat_msg(const Quaternionf &q_src , geometry_msgs::Quaternion_<std::allocator<void> > &quat_msg)
{
    quat_msg.w = q_src.w();
    quat_msg.x = q_src.x();
    quat_msg.y = q_src.y();
    quat_msg.z = q_src.z();
}

// @brief: copy double xyz point msg to Vertor3f
void gene_math_copy_point_msg_to_v3f(Vector3f &v_des , const geometry_msgs::Point_<std::allocator<void> > &point_msg)
{
    v_des(0) = (float)point_msg.x;
    v_des(1) = (float)point_msg.y;
    v_des(2) = (float)point_msg.z;
}

// @brief: copy double wxyz msg to Vertor4f
void gene_math_copy_quat_msg_to_v4f(Quaternionf &q_des , const geometry_msgs::Quaternion_<std::allocator<void> > &quat_msg)
{
    q_des.w() = (float)quat_msg.w;
    q_des.x() = (float)quat_msg.x;
    q_des.y() = (float)quat_msg.y;
    q_des.z() = (float)quat_msg.z;
}

// @brief: copy double xyz vector msg to Vertor3f
void gene_math_copy_vector_msg_to_v3f(Vector3f &v_des , const geometry_msgs::Vector3_<std::allocator<void> > &vector_msg)
{
    v_des(0) = (float)vector_msg.x;
    v_des(1) = (float)vector_msg.y;
    v_des(2) = (float)vector_msg.z;
}