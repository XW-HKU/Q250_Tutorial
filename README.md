# VINS Project

`src/mavros`-communication with pixhawk4

`src/mocap_optitrack`-read the optitrack datas

`src/offboard`-generate the path and pass to px4

`src/mavlink`-the communication protocol of pixhawk4

`catkin_ws/src/VINS_Fusion`- the ros SLAM opensource package VINS

## Normal Steps

1. `cd MaRS_Offboard`
2. `catkin build`
3. `source devel/setup.bash`
4. `roslaunch mocap_optitrack mocap.launch`
5. open a new terminal and move into MaRS_Offboard directory
6. `source devel/setup.bash`
7. `roslaunch mavros px4.launch`
8. open a new terminal and move into MaRS_Offboard directory
9. `source devel/setup.bash`
10. `rosrun offboard offboard_node`

after these steps, arm the pixhawk and switch into offboard mode through RC, the UAV will autonomous fly.

## To use VINS for loclization:
```
cd catkin_ws
catkin_make
source devel/setup.bash
```
Then following the following steps:

1. Enable realsense camera:
```
roslaunch realsense2_camera rs_camera.launch  # without imu
roslaunch realsense2_camera_camera_tianyu.launch # with imu
```
2. Enanle pixhawk:
```
roslaunch mavros px4.launch 
rosrun mavros mavcmd long 511 31 500 0 0 0 0 0 # to improve the rate of imu topic
```
3. Enable VINS:
```
roslaunch vins vins_node.launch
(optional) rosrun loop_fusion loop_fusion_node ~/config/realsense/realsense_stereo_imu_config.yaml
```



