# Software Challenge

This repository will act as a starting point for new developers in order to help them understand some of the fundamentals of ROS2 and Gazebo, and to guide the installation of the Ubuntu OS.

# Ubuntu 20.04 installation guide

ROS2 and our robot's on-board computer (Nvidia TX2) use on a linux distribution to operate, for our development work we will be using Ubuntu 20.04 preferably dual booted alongside Windows. Developing in linux using a Mac machine is generally not recommended but if there is no option please follow the dual-booting instructions below **using an Ubuntu 20.04 image** or explore virtual box options. 

For this tutorial, you'll need a blank, >4 GB stoarge USB stick. 

For dual-booting: 
Different brands of computer may encounter manufacturer-specific blocks, please refer to the documentation relevant to your machine for solutions. 
* [Windows Subsystem for Linux (WSL) 2](https://docs.microsoft.com/en-us/windows/wsl/install-win10)
  * This option has not been throughly tested, however ROS2 and other GUI applications can install and run successfully
  * The linked instructions require Windows 10 build 1903 or higher to install (check using 'winver'), follow the manual instructions to ensure WSL is upgraded
  * If you've installed Windows build 21364 or higher (check using the program, winver), you will be able to run GUI application autmatically, if you have not, continue with the next instruction
  * After enabling the kernel and installing Ubunutu 20.04, install [VcXsrv](https://sourceforge.net/projects/vcxsrv/)
  * Start the service (XLanuch) and enter these configurations:
     * First screen: select "Multiple Windows", Display number = -1
     * Second Screen: select "Start no client"
     * Third Screen: check "Clipboard", uncheck "Native opengl", check "Disable Access Control" 
     * Select finish
  * Finally, in your Ubuntu 20.04 terminal, run the command:

`echo "export GAZEBO_IP=127.0.0.1" >> ~/.bashrc && echo "export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0 " >> ~/.bashrc && echo "export LIBGL_ALWAYS_INDIRECT=0" >> ~/.bashrc`

  * After a restart, you should now have a functional Ubuntu virtual machine, you can test your GUI by installing firefox (`sudo apt-get install -y firefox`) and running it with `firefox`

* [Windows Instructions](https://www.tecmint.com/install-ubuntu-alongside-with-windows-dual-boot/)
  * Make bootable USB with [Rufus](https://rufus.ie/)
  * Note: BIOS can also be accessed by restarting using Recovery options menu in windows.
* [Mac Instructions](https://www.maketecheasier.com/install-dual-boot-ubuntu-mac/)
  
# Windows - Docker
There is a new option, to use Docker for development
* Install [Docker](https://www.docker.com/get-started/)
* Install [WSL](https://learn.microsoft.com/en-us/windows/wsl/install)
* install [VcXsrv](https://sourceforge.net/projects/vcxsrv/)
* Run `docker pull hashaam1217/ubc_subbots:1.1`
* Start the service (XLanuch) and enter these configurations:
     * First screen: select "Multiple Windows", Display number = -1
     * Second Screen: select "Start no client"
     * Third Screen: check "Clipboard", uncheck "Native opengl", check "Disable Access Control" 
     * Select finish
* Run `docker run -it --name ubc_subbots -e DISPLAY=host.docker.internal:0 -v /tmp/.X11-unix:/tmp/.X11-unix hashaam1217/ubc_subbots:1.1` in terminal as adminstrator
* To open another terminal connected to the same OS, run `docker exec -it ubc_subbots /bin/bash`
* It should be already installed with all tools neccessary to work with ROS2.
* This is a stateless system, you're changes are not saved so make you sure you push your changes to github before exiting

### Saving your image (optional)
* If you want to save your image you can do it in a few steps.
* Use `docker ps -a` to view the last container you have opened.
* We can use `docker commit [Your old container ID or name] [Name of the new image]` to save our last workspace for future use.
* For example the name of the first container is "ubc_subbots". We can use `docker commit ubc_subbots my_local_image` to save your last container for future use.
* You will have to modify the run command like this: `docker run -it -e DISPLAY=host.docker.internal:0 -v /tmp/.X11-unix:/tmp/.X11-unix my_local_image`

Once Ubuntu is installed, you will need to install a preferred IDE. Some suggestions are listed below: 

* [Eclipse](https://www.eclipse.org/ide/)
* [Clion](https://www.jetbrains.com/clion/) (can be tedious to setup, requires an account) 
* [VS Code](https://code.visualstudio.com/) (strenuous setup but very powerful IDE) 

# Git command line tools 

To use Git from the linux command line, follow the install [here](https://linuxize.com/post/how-to-install-git-on-ubuntu-20-04/)

# ROS2 Installation

To install ROS2, follow the tutorial [here](https://index.ros.org/doc/ros2/Installation/Foxy/Linux-Install-Debians/), please install the desktop version. 

Next, you will need to install the ROS2 build tools (Colcon). Please follow the guide [here](https://index.ros.org/doc/ros2/Tutorials/Colcon-Tutorial/#install-colcon)

# Gazebo 11 Installation 

Gazebo is a simulation environment which we will be using to test our robot's computer vision and control algorithms, use the "Default installation" option [here](http://gazebosim.org/tutorials?tut=install_ubuntu&cat=install) to download the application and then run the command: "sudo apt install ros-foxy-gazebo-ros-pkgs"  adapted from the instructions [here](http://gazebosim.org/tutorials?tut=ros2_installing&cat=connect_ros#Installgazebo_ros_pkgs) to install the ROS2 plugins. 

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
