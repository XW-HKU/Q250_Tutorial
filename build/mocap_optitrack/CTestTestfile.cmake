# CMake generated Testfile for 
# Source directory: /home/dji/MaRS_Offboard/src/mocap_optitrack
# Build directory: /home/dji/MaRS_Offboard/build/mocap_optitrack
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(_ctest_mocap_optitrack_roslaunch-check_launch "/home/dji/MaRS_Offboard/build/mocap_optitrack/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/kinetic/share/catkin/cmake/test/run_tests.py" "/home/dji/MaRS_Offboard/build/mocap_optitrack/test_results/mocap_optitrack/roslaunch-check_launch.xml" "--return-code" "/usr/bin/cmake -E make_directory /home/dji/MaRS_Offboard/build/mocap_optitrack/test_results/mocap_optitrack" "/opt/ros/kinetic/share/roslaunch/cmake/../scripts/roslaunch-check -o '/home/dji/MaRS_Offboard/build/mocap_optitrack/test_results/mocap_optitrack/roslaunch-check_launch.xml' '/home/dji/MaRS_Offboard/src/mocap_optitrack/launch' ")
subdirs(gtest)
subdirs(src)
