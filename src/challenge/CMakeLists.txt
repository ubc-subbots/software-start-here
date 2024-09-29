cmake_minimum_required(VERSION 3.5)
project(challenge)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)

# Add the executable
add_executable(solution src/solution.cpp)
ament_target_dependencies(solution rclcpp geometry_msgs)

# Install the target
install(TARGETS solution
  DESTINATION lib/${PROJECT_NAME})

ament_package()
