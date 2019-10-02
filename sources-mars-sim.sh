#!/bin/bash

if [ ! -d "/src/Firmware_xw" ]; then
  cd $(pwd)/src
  git clone https://github.com/WeiBUAA/Firmware-xw.git
  cd ..
fi

catkin build

source $(pwd)/devel/setup.bash

source $(pwd)/src/setup_gazebo.bash $(pwd) $(pwd)

echo -e "ROS_PACKAGE_PATH $ROS_PACKAGE_PATH"
