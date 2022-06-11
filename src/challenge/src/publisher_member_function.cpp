// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <math.h>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include <geometry_msgs/msg/twist.hpp>

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
 * member function as a callback from the timer. */

class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher()
  : Node("minimal_publisher"), count_(0)
  {
    publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
    timer_ = this->create_wall_timer(
      50ms, std::bind(&MinimalPublisher::timer_callback, this));
  }

private:
  void timer_callback()
  {
    // auto message = std_msgs::msg::String();
    // message.data = "Trying the challenge! " + std::to_string(count_++);

    auto controls = geometry_msgs::msg::Twist();
    // controls.linear.x = "{linear: {x: 2.0, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 1.8}}";

    if (start >= 2){
      
      if (UP == 0 && angle_z == 5.0 ) {
        UP = 1;
      }

      if (UP == 1 && angle_z == -5.0){
        UP = 0;
      }

      if (UP == 1) {
        angle_z = angle_z - 0.5;
      }
      else {
        angle_z = angle_z + 0.5;
      }

    }

    start++;

    

    controls.linear.x = 1.0;
    controls.linear.y = 0.0;
    controls.linear.z = 0.0;

    controls.angular.x = 0.0;
    controls.angular.y = 0.0;
    controls.angular.z = angle_z;


    // RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", controls.data.c_str());
    // publisher_->    angle_z++;publish(message);

    publisher_->publish(controls);

  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
  size_t count_;

  int start = 0;
  
  double angle_z = 5;
  
  int UP = 0;


};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
