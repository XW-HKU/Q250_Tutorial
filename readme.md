## Run Full Simulator Inside the ROS (PX4, Gazebo, MAVROS, OFFBOARD)
PX4 SITL + Gazeb
dependencies:
1. if you install gazebo9, gazebo_ros should be installed as: `sudo apt-get install ros-kinetic-gazebo9-ros*`
2. install the mavros package dependencies `https://github.com/mavlink/mavros/blob/master/mavros/README.md#installation`, especially the section `Binary installation (deb)`
3. if the catkin build show error at the beginning, source the neccesary direction to the .basrc in the \home folder.

Guide of Run
1. `cd MaRS_Offboard`
2. `source sources-mars-sim.sh`
3. `roslaunch mars-sim.launch`

Noted:
1. If you just want to develope the simulator, you don't need to pay attention to Firmware_xw which is linked to our flight controller project.

## Software In The Loop (SITL) Simulation + Offboard:

0. Open the vehicle model's sdf file (e.g. **/src/sitl_gazebo/models/iris/iris.sdf**).
Under the `mavlink_interface plugin` section, change the `serialEnabled` and `hil_mode` parameters to `false`.
1. `make px4_sitl_default gazebo`
2. `roslaunch mavros px4.launch fcu_url:="udp://:14540@127.0.0.1:14550"`
3. `rosrun offboard offboard_node`

## Hardware In The Loop (HITL) simulation
HITL+Offboard

1. connect computer to flight controller hardware
2. `roslaunch mavros px4.launch fcu_url:="udp://:14540@127.0.0.1:14550"`
3. Open the vehicle model's sdf file (e.g. **/src/sitl_gazebo/models/iris/iris.sdf**).
Under the `mavlink_interface plugin` section, change the `serialEnabled` and `hil_mode` parameters to `true`.
4. `source Tools/setup_gazebo.bash $(pwd) $(pwd)/build/px4_sitl_default`
5. `gazebo Tools/sitl_gazebo/worlds/iris.world`
6. `rosrun offboard offboard_node`



