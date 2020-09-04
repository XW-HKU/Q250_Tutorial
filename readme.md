## Run Full Simulator Inside the ROS (PX4, Gazebo, MAVROS, OFFBOARD)
PX4 SITL + Gazeb
### dependencies:
1. if you install gazebo9, gazebo_ros should be installed as: `sudo apt-get install ros-kinetic-gazebo9-ros*`
2. install the mavros package dependencies `https://github.com/mavlink/mavros/blob/master/mavros/README.md#installation`, especially the section `Binary installation (deb)`
3. if the catkin build show error at the beginning, source the neccesary direction to the .basrc in the \home folder.

### Run Gazebo Simulator (quadrotor)
1. `cd MaRS_Offboard`
2. `source sources-mars-sim.sh && cd VTOL-FC && make px4_sitl gazebo`
4. if you want to simulate the flihgt mission, directly open the QGroundControl software, than use the mission function as usal.

### Software In The Loop (SITL) Offboard Mode Simulation 
0. Open the vehicle model's sdf file (e.g. **/src/VTOL-FC/Tool/sitl_gazebo/models/iris/iris.sdf**).
Under the `mavlink_interface plugin` section, change the `serialEnabled` and `hil_mode` parameters to `false`.

1. open a new terminal and cd into MaRS_Offboard
2. `source sources-mars-sim.sh`
3. `roslaunch mavros px4.launch fcu_url:="udp://:14540@127.0.0.1:14550"`
4. open a new terminal
5. `source sources-mars-sim.sh`
6. `rosrun offboard offboard_node`

## Hardware In The Loop (HITL) simulation
HITL+Offboard

1. connect computer to flight controller hardware
2. `roslaunch mavros px4.launch fcu_url:="udp://:14540@127.0.0.1:14550"`
3. Open the vehicle model's sdf file (e.g. **/src/sitl_gazebo/models/iris/iris.sdf**).
Under the `mavlink_interface plugin` section, change the `serialEnabled` and `hil_mode` parameters to `true`.
4. `source Tools/setup_gazebo.bash $(pwd) $(pwd)/build/px4_sitl_default`
5. `gazebo Tools/sitl_gazebo/worlds/iris.world`
6. `rosrun offboard offboard_node`



