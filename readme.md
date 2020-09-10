## Run Full Simulator Inside the ROS (PX4, Gazebo, MAVROS, OFFBOARD)
PX4 SITL + Gazeb
### dependencies:
1. if you install gazebo9, gazebo_ros should be installed as: `sudo apt-get install ros-kinetic-gazebo9-ros*`
2. install the mavros package dependencies `https://github.com/mavlink/mavros/blob/master/mavros/README.md#installation`, especially the section `Binary installation (deb)`
3. if the catkin build show error at the beginning, source the neccesary direction to the .basrc in the \home folder.

### Run Gazebo Simulator (quadrotor)
for the first time

1. `cd MaRS_Offboard`
2. `git submodule update --init --recursive --remote`
3. `catkin build`

Then:

1. `cd src/VTOL-FC`
2. `make px4_sitl gazebo`
3. if you want to simulate the flight mission, directly open the QGroundControl software, than use the mission function as usal.

### Software In The Loop (SITL) Offboard Mode Simulation 
0. Open the vehicle model's sdf file (e.g. **/src/VTOL-FC/Tool/sitl_gazebo/models/iris/iris.sdf**).
Under the `mavlink_interface plugin` section, change the `serialEnabled` and `hil_mode` parameters to `false`.

1. open a new terminal and cd into MaRS_Offboard
3. `source sources-mars-sim.sh`
4. `roslaunch mavros px4.launch fcu_url:="udp://:14540@127.0.0.1:14550"`
5. open a new terminal
6. `source sources-mars-sim.sh`
7. `rosrun offboard offboard_node`

## Hardware In The Loop (HITL) simulation
HITL+Offboard

1. connect computer to flight controller hardware
2. `roslaunch mavros px4.launch fcu_url:="udp://:14540@127.0.0.1:14550"`
3. Open the vehicle model's sdf file (e.g. **/src/sitl_gazebo/models/iris/iris.sdf**).
Under the `mavlink_interface plugin` section, change the `serialEnabled` and `hil_mode` parameters to `true`.
4. `source Tools/setup_gazebo.bash $(pwd) $(pwd)/build/px4_sitl_default`
5. `gazebo Tools/sitl_gazebo/worlds/iris.world`
6. `rosrun offboard offboard_node`


## Trajectory tracking 
The default is a horizontal trajectory like "8", which requires flight control parameter tuning. If you want another trajectory that requires no any tunings, switch "traj_mode" in <**/src/offboard/src/offboard_node.cpp> to "HOVER", save and `catkin build` the project.

For the default trajectory,  parameter reference of simulator and Q250+realsence can be respectfully found in <*/src/offboard/FC_para>.


