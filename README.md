# Software Challenge

A set of Ubuntu, Gazebo and ROS 2 examples and projects to help new Subbots Software team members.

This repository will act as a starting point for new developers in order to help them understand some of the fundamentals of ROS 2 and Gazebo, and to guide the installation of the Ubuntu OS.

# Ubuntu 20.04 installation guide

ROS 2 and our robot's on-board computer (Nvidia TX2) use on a linux distribution to operate, for our development work we will be using Ubuntu 20.04 preferably dual booted alongside windows. Developing in linux using a Mac machine is generally not recommended but if there is no option please follow the dual-booting instructions below **using an Ubuntu 20.04 image** or explore virtual box options. 

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

To use Git from the linux command line, follow the install [here](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git)

# ROS 2 Installation

To install ROS 2, follow the tutorial [here](https://index.ros.org/doc/ros2/Installation/Foxy/Linux-Install-Debians/), please install the desktop version. 

Next, you will need to install the ROS 2 build tools (Colcon). Please follow the guide [here](https://index.ros.org/doc/ros2/Tutorials/Colcon-Tutorial/#install-colcon)

# ROS 2 Beginners Guide

The [ROS 2 Wiki](https://index.ros.org/doc/ros2/Tutorials/) contains many helpful tutorials that teach the fundamentals of the operating system. We recommend completing as many of them as you need to from the Beginners set. As well, any other tutorials beyond would be benefical. 

# The challenge 

Using the Turtlesim package, you will write a node that commands the turtle to perform a sine motion using the information available in the ROS 2 wiki. 
1. Open a new cmd prompt, clone this repository onto your machine and switch to the resulting folder.
2. Create a new branch using the convention, challenge/<your name>.
3. Inside this directory, create a folder named "src" (use cmd commands) and change directory to this folder.
3. Create a ROS 2 C++ package inside the repository named "challenge" with a node named "solution" (ROS 2 tutorials refer to dev_ws/src, in your case this should be software-start-here/src).
4. 
