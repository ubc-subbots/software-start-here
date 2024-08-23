cmake_minimum_required(VERSION 3.8)
project(challenge)

# Set C++ standard to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

add_executable(solution src/solution.cpp)
ament_target_dependencies(solution rclcpp)

install(TARGETS
  solution
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
