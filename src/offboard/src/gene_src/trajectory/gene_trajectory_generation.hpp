#ifndef  GENE_TRAJECTORY_GENERATION_H
#define  GENE_TRAJECTORY_GENERATION_H
#include <stdint.h>
#include "../math/gene_math.hpp"
#include "../message/gene_ros_msg.hpp"


#define DATA_ROW 1101
#define DATA_COL 18
#define TAKEOFF_TIME (3*OFFBORAD_RUN_RATE)
#define HOVER_TIME (7*OFFBORAD_RUN_RATE)
#define PRIOR_TIME (TAKEOFF_TIME + HOVER_TIME)
#define WAIT_TIME (5*OFFBORAD_RUN_RATE)

typedef float traj_data_t[DATA_ROW][DATA_COL];

enum traj_mode_t  
{HOVER,
 TRAJ_1,
 TRAJ_2,
 TRAJ_3,
 TRAJ_4};

 struct traj_t
 {
     traj_mode_t                                        mode;
     uint32_t                                           wait_cnt;
     uint32_t                                           read_cnt;
     geometry_msgs::Pose_<std::allocator<void> >        initial_pose;

     Vector3f                                           pos;            // local position,      unit: m
     Vector3f                                           vel;            // local velocity,      unit: m/s
     Vector3f                                           acc;            // local acceleration,  unit: m/s^2
     Vector3f                                           omega;          // body angular rate,   unit: rad/s
     float                                              yaw;            // Euler yaw,           unit: rad
     float                                              a_T;            // thrust acceleration, unit: N/kg or m/s^2
     Quaternionf                                        q;              // quaternion,          order: wxyz
 };


void gene_traj_data_read(traj_t &traj, const traj_data_t &traj_data);
void gene_offline_traj_generate(traj_t &traj, const traj_data_t &traj_data, geometry_msgs::Pose_<std::allocator<void> > &pose);

#endif