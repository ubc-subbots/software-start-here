cmake_minimum_required(VERSION 3.8)
project(cpp_pub) # <-- IMPORTANT: Change this to your actual package name

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(turtlesim REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_srvs REQUIRED)

# This is the line we are fixing.
# We are telling CMake to build a program named 'turtle_publisher_node'
# using the source file 'src/turtle_publisher.cpp'.
add_executable(turtle_publisher_node src/turtle_publisher.cpp)

# Link the libraries your program needs
ament_target_dependencies(turtle_publisher_node
  rclcpp
  geometry_msgs
  turtlesim
  std_srvs
)

# Install the program so 'ros2 run' can find it
install(TARGETS
  turtle_publisher_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
