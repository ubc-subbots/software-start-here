cmake_minimum_required(VERSION 3.5)
project(challenge)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(turtlesim REQUIRED)
find_package(geometry_msgs REQUIRED)  # Add geometry_msgs, needed for Twist message

# Add the executable and specify the source file
add_executable(solution src/solution.cpp)

# Link the executable with required dependencies
ament_target_dependencies(solution rclcpp turtlesim geometry_msgs)

# Install the executable so it can be run with ros2 run
install(TARGETS
  solution
  DESTINATION lib/${PROJECT_NAME})

# Linter setup (optional, already present in your CMakeLists.txt)
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
