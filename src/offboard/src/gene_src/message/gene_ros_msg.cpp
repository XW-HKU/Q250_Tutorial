#include "gene_ros_msg.hpp"

// @brief: receive feedback data from ros msg
void gene_feedback_msg_receive(feedback_t &fb,
                               geometry_msgs::PoseStamped  &local_pose,
                               geometry_msgs::TwistStamped &local_twist,
                               geometry_msgs::TwistStamped &body_twist)
{
    gene_math_copy_point_msg_to_v3f(fb.pos , local_pose.pose.position);
    gene_math_copy_quat_msg_to_v4f(fb.q_eb , local_pose.pose.orientation);

    gene_math_copy_vector_msg_to_v3f(fb.vel , local_twist.twist.linear);

    gene_math_copy_vector_msg_to_v3f(fb.vel_body , body_twist.twist.linear);
    gene_math_copy_vector_msg_to_v3f(fb.omega , body_twist.twist.angular);

    fb.R_eb = fb.q_eb.normalized().toRotationMatrix();

}

//@brief: save log data to std::vector
void gene_log_save(log_t &log_data , float time_stamp, feedback_t &fb, traj_t &traj)
{
    Eigen::Matrix<float, 1, LOG_NUM> log_per_tick;

    /* feedback data */
    log_per_tick(0,0) = time_stamp;                         // 0
    log_per_tick(0,1) = fb.q_eb.w();                        // 1~4
    log_per_tick(0,2) = fb.q_eb.x();
    log_per_tick(0,3) = fb.q_eb.y();
    log_per_tick(0,4) = fb.q_eb.z();
    log_per_tick.block<1,3>(0,5) = fb.pos;                  // 5~7
    log_per_tick.block<1,3>(0,8) = fb.vel;                  // 8~10
    log_per_tick.block<1,3>(0,11) = fb.acc;                 // 11~13
    log_per_tick.block<1,3>(0,14) = fb.omega;               // 14~16
    log_per_tick.block<1,3>(0,17) = fb.ang_acc;             // 17~19
    
    /* trajectory data */
    log_per_tick(0,20) = traj.q.w();                        // 20~23
    log_per_tick(0,21) = traj.q.x();
    log_per_tick(0,22) = traj.q.y();
    log_per_tick(0,23) = traj.q.z();
    log_per_tick.block<1,3>(0,24) = traj.pos;               // 24~26
    log_per_tick.block<1,3>(0,27) = traj.vel;               // 27~29
    log_per_tick.block<1,3>(0,30) = traj.omega;             // 30~32
    

    log_data.push_back(log_per_tick);
}