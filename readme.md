## Run Full Simulator Inside the ROS (PX4, Gazebo, MAVROS, OFFBOARD)
PX4 SITL + Gazebo
1. copy all the files in **MaRS_Offboard/** to a catkin workspace
2. `catkin build`
3. `source sources-mars-sim.sh`
4. `roslaunch mars-sim.launch`

Noted:
1. If you just want to develope the simulator, you don't need to pay attention to Firmware_xw which is linked to our flight controller project.

## Using the Offboard Control With the Independent PX4 Firmware:

SITL + Offboard:

0. Open the vehicle model's sdf file (e.g. **Tools/sitl_gazebo/models/iris/iris.sdf**).
Under the `mavlink_interface plugin` section, change the `serialEnabled` and `hil_mode` parameters to `false`.
1. `make px4_sitl_default gazebo`
2. `roslaunch mavros px4.launch fcu_url:="udp://:14540@127.0.0.1:14550"`
3. `rosrun offboard offboard_node`


HITL+Offboard

1. connect computer to flight controller hardware
2. `roslaunch mavros px4.launch fcu_url:="udp://:14540@127.0.0.1:14550"`
3. Open the vehicle model's sdf file (e.g. **Tools/sitl_gazebo/models/iris/iris.sdf**).
Under the `mavlink_interface plugin` section, change the `serialEnabled` and `hil_mode` parameters to `true`.
4. `source Tools/setup_gazebo.bash $(pwd) $(pwd)/build/px4_sitl_default`
5. `gazebo Tools/sitl_gazebo/worlds/iris.world`
6. `rosrun offboard offboard_node`



