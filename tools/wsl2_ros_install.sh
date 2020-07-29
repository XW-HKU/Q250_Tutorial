sudo apt update
sudo apt upgrade
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654
sudo apt update
sudo apt upgrade
sudo apt install ros-melodic-desktop-full catkin
sudo cp /etc/skel/.bashrc ~/
echo "source /opt/ros/melodic/setup.bash" >> ~/.bashrc
cd ~
source ~/.bashrc
sudo apt-get install ros-melodic-eigen3* ros-melodic-pcl* ros-melodic-sophus*
mkdir Livox_ros_driver && cd Livox_ros_driver
mkdir src && cd src
git clone https://github.com/Livox-SDK/livox_ros_driver.git
cd .. && catkin_make -j8
echo "source ~/Livox_ros_driver/devel/setup.sh" >> ~/.bashrc