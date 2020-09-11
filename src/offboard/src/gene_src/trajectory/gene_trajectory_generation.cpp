#include "gene_trajectory_generation.hpp"

void gene_traj_data_read(traj_t *traj, const traj_data_t traj_data)
{
    uint32_t read_row;
    
    read_row = traj->read_cnt;

    memcpy(traj->pos.data(),   &traj_data[read_row][0], 3*sizeof(float));
    memcpy(traj->vel.data(),   &traj_data[read_row][3], 3*sizeof(float));
    memcpy(traj->acc.data(),   &traj_data[read_row][6], 3*sizeof(float));
    memcpy(traj->omega.data(), &traj_data[read_row][9], 3*sizeof(float));

    traj->yaw = traj_data[read_row][12];
    traj->a_T = traj_data[read_row][13];

    // gene_math_copy_wxyz_array_to_xyzw_quatf(&traj_data[read_row][14], traj->q);  // Todo: wrong memery
    traj->q.w() = traj_data[read_row][14];
    traj->q.x() = traj_data[read_row][15];
    traj->q.y() = traj_data[read_row][16];
    traj->q.z() = traj_data[read_row][17];
}

void gene_offline_traj_generate(traj_t *traj, const traj_data_t traj_data, geometry_msgs::Pose_<std::allocator<void> > *pose)
{
    if (traj->wait_cnt < WAIT_TIME)
    {
        traj->wait_cnt ++;
        pose->position.x = 0.0f;
        pose->position.y = 0.0f;
        pose->position.z = 0.0f;
        
    }
    else
    {
        switch (traj->mode)
        {
            case HOVER:
                if (traj->read_cnt < PRIOR_TIME)
                {
                    traj->read_cnt ++;
                }

                gene_traj_data_read(traj, traj_data);
                break;

            case TRAJ_1:
                traj->read_cnt ++;
                if (traj->read_cnt >= DATA_ROW)
                {
                    traj->read_cnt = PRIOR_TIME;
                }

                gene_traj_data_read(traj, traj_data);
                
                break;

            // case TRAJ_2:
            //     traj_cnt ++;
            //     if (traj_cnt < PRIOR_TIME)
            //     {
            //         gene_math_v3_copy_to_xyz(&traj_data[traj_cnt][0] , &pose.pose.position);
            //         gene_math_wxyz_copy_to_wxyz(&last_pose.pose.orientation , &pose.pose.orientation);
            //     }
            //     else if (traj_cnt < PRIOR_TIME + 5 * 50)
            //     {
            //         gene_math_v3_copy_to_xyz(&traj_data[PRIOR_TIME][0] , &pose.pose.position);

            //         pose.pose.orientation.w = 1.0f;
            //         pose.pose.orientation.x = 0.0f;
            //         pose.pose.orientation.y = 0.0f;
            //         pose.pose.orientation.z = 0.0f;
            //     }
            //     else if (traj_cnt < PRIOR_TIME + 5 * 50 + HOVER_TIME)
            //     {
            //         gene_math_v3_copy_to_xyz(&traj_data[PRIOR_TIME][0] , &pose.pose.position);
            //         pose.pose.position.x += traj_data[traj_cnt - PRIOR_TIME - 5 * 50][2];

            //         pose.pose.orientation.w = 1.0f;
            //         pose.pose.orientation.x = 0.0f;
            //         pose.pose.orientation.y = 0.0f;
            //         pose.pose.orientation.z = 0.0f;
            //     }
            //     else
            //     {
            //         gene_math_v3_copy_to_xyz(&traj_data[PRIOR_TIME][0] , &pose.pose.position);
            //         pose.pose.position.x += traj_data[PRIOR_TIME][2];

            //         pose.pose.orientation.w = 1.0f;
            //         pose.pose.orientation.x = 0.0f;
            //         pose.pose.orientation.y = 0.0f;
            //         pose.pose.orientation.z = 0.0f;
            //     }   
                
            //     break;

            default:
                break;

        }

        /* set msg */
        gene_math_v3f_copy_to_point_msg(traj->pos , &pose->position);
        gene_math_v4f_copy_to_quat_msg(traj->q, &pose->orientation);
    }
    
}


