# Software Challenge

This repository will act as a starting point for new developers in order to help them understand some of the fundamentals of ROS2 and Gazebo, and to guide the installation of the Ubuntu OS.

# Ubuntu 20.04 installation guide

ROS2 and our robot's on-board computer (Nvidia TX2) use on a linux distribution to operate, for our development work we will be using Ubuntu 20.04 preferably dual booted alongside Windows. Developing in linux using a Mac machine is generally not recommended but if there is no option please follow the dual-booting instructions below **using an Ubuntu 20.04 image** or explore virtual box options. 

For this tutorial, you'll need a blank, >4 GB stoarge USB stick. 

For dual-booting: 
Different brands of computer may encounter manufacturer-specific blocks, please refer to the documentation relevant to your machine for solutions. 
* [Windows Instructions](https://www.tecmint.com/install-ubuntu-alongside-with-windows-dual-boot/)
  * Note: BIOS can also be accessed by restarting using Recovery options menu in windows. 
* [Mac Instructions](https://www.maketecheasier.com/install-dual-boot-ubuntu-mac/)
  
Once Ubuntu is installed, you will need to install a preferred IDE. Some suggestions are listed below: 

* [Eclipse](https://www.eclipse.org/ide/)
* [Clion](https://www.jetbrains.com/clion/) (can be tedious to setup, requires an account) 
* [VS Code](https://code.visualstudio.com/) (strenuous setup but very powerful IDE) 

# Git command line tools 

To use Git from the linux command line, follow the install [here](https://linuxize.com/post/how-to-install-git-on-ubuntu-20-04/)

# ROS2 Installation

To install ROS2, follow the tutorial [here](https://index.ros.org/doc/ros2/Installation/Foxy/Linux-Install-Debians/), please install the desktop version. 

Next, you will need to install the ROS2 build tools (Colcon). Please follow the guide [here](https://index.ros.org/doc/ros2/Tutorials/Colcon-Tutorial/#install-colcon)

# Gazebo 11.0 Installation 

Gazebo is a simulation environment which we will be using to test our robot's computer vision and control algorithms, use the "Default installation" option [here](http://gazebosim.org/tutorials?tut=install_ubuntu&cat=install) to download the application and the instructions [here](http://gazebosim.org/tutorials?tut=ros2_installing&cat=connect_ros#Installgazebo_ros_pkgs) to install the ROS2 plugins.  

# ROS2 Index

The [ROS2 Index](https://index.ros.org/doc/ros2/) is the main source of information about the framework. To get a solid understanding of ROS2 concepts, follow along with all of the beginner tutorials [here](https://index.ros.org/doc/ros2/Tutorials/#tutorials). It's reccomended to look through all of the intermediate and advanced tutorials as well as we will use concepts explained in these regularily.

# The Challenge 

Using the Turtlesim package, you will write a node that commands the turtle to perform a sine motion using the information available in the ROS2 wiki. 
1. Open a new cmd prompt, clone this repository onto your machine and switch to the resulting folder.
2. Create a new branch using the convention, challenge/{your name}.
3. Inside this directory, create a folder named "src" (use cmd commands) and change directory to this folder.
4. Create a ROS 2 C++ package inside the repository named "challenge" with a node named "solution" (ROS2 tutorials refer to dev_ws/src, in your case this should be software-start-here/src).
5. Fill in your node so that it can command the turtlesim node to perform a sine motion. 
6. **Bonus** Write a launch file to launch a turtlesim node and your node together. 
7. push your node to Git and let Jake or Logan know that you've completed the challenge!
