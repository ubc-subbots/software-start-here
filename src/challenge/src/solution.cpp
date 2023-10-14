#include <cstdio>
#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <ctime>
#include <cmath>

#include "turtlesim/msg/pose.hpp"
#include "turtlesim/srv/spawn.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class TurtleSimController : public rclcpp::Node
{
public:
  TurtleSimController()
  : Node("turtle_sim_controller") 
  {
    publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 10);
    timer_ = this->create_wall_timer(100ms, std::bind(&TurtleSimController::timer_callback, this)); 
  }

private:
  int i_ = 0;
  
  void timer_callback()
  {
      i_ += 10;
      auto message = geometry_msgs::msg::Twist();
      message.linear.x = 1.0;
      message.linear.y = 10 * sin(i_ * 3.1415 / 180.0);
      message.linear.z = 0.0;
      message.angular.x = 0.0;
      //message.angular.y = 5 * sin(i_ * 3.1415 / 180.0);
      message.angular.y = 0;

      message.angular.z = 0.0;
      RCLCPP_INFO(this->get_logger(), "Publishing: '%f'", message.linear.y);
      RCLCPP_INFO(this->get_logger(), "i: '%i'", i_);
      publisher_->publish(message);
  }
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;



};



int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TurtleSimController>());
  rclcpp::shutdown();
  printf("hello world challenge package\n");
  return 0;
}
