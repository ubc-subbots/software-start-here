FROM ubuntu:20.04

# Standard updating
RUN apt-get update -y && \
    apt-get install -y \
    build-essential \
    git \
    curl \
    wget \
    python3 \
    python3-pip \
    && apt-get clean

# Allows us to use sudo
RUN apt-get -y install sudo

# Reduce interactive prompts during installation
RUN export DEBIAN_FRONTEND=noninteractive

## ROS2 Installation

# Locale
RUN apt install locales
RUN locale-gen en_US en_US.UTF-8
RUN update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
RUN export LANG=en_US.UTF-8

# Sources
RUN DEBIAN_FRONTEND=noninteractive apt-get -y install tzdata



RUN apt install software-properties-common -y
RUN add-apt-repository universe

# GPG Key
RUN apt update && sudo apt install curl -y
RUN curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
RUN echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null

RUN apt update -y && apt upgrade -y
RUN apt install ros-foxy-desktop python3-argcomplete -y
RUN apt install ros-dev-tools -y

## Gazebo
RUN apt-get update && apt-get install -y ros-foxy-gazebo-ros-pkgs  
RUN apt-get install xorg -y
RUN echo "export GAZEBO_IP=127.0.0.1" >> ~/.bashrc && echo "export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0 " >> ~/.bashrc && echo "export LIBGL_ALWAYS_INDIRECT=0" >> ~/.bashrc

RUN apt install neovim -y
RUN apt install vim -y


# Creating a user 
RUN useradd -m software
RUN usermod -aG sudo software
RUN echo 'software ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers.d/software
RUN echo 'software:password' | chpasswd
USER software
WORKDIR /home/software

RUN echo "source /opt/ros/foxy/setup.bash" >> ~/.bashrc
RUN echo "echo "Hello, welcome to Ubuntu 20.04 with ROS2 installed"" >> ~/.bashrc
RUN echo "echo "Hashaam Zafar - 2023"" >> ~/.bashrc
RUN echo "echo "Contact Hzafar04@student.ubc.ca for any questions."" >> ~/.bashrc
RUN echo "echo """ >> ~/.bashrc


