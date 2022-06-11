cmake_minimum_required(VERSION 3.5)
project(challenge)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

find_package(geometry_msgs REQUIRED)

add_executable(solution src/publisher_member_function.cpp)
ament_target_dependencies(solution rclcpp geometry_msgs)


add_executable(listener src/subscriber_member_function.cpp)
ament_target_dependencies(listener rclcpp std_msgs)




install(TARGETS
  solution
  listener
  DESTINATION lib/${PROJECT_NAME})
  
ament_package()