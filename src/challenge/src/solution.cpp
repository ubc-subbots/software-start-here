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
    timer_ = this->create_wall_timer(500ms, std::bind(&TurtleSimController::timer_callback, this)); 
  }

private:
  void timer_callback()
  {
      auto message = geometry_msgs::msg::Twist();
      message.linear.x = 1.0;
      message.linear.y = 0.0;
      message.linear.z = 0.0;
      message.angular.x = 0.0;
      message.angular.y = sine_function();
      message.angular.z = 0.0;
      //RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
      publisher_->publish(message);
  }
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;

double sine_function()
{
    return sin(time(0));
}
};



int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TurtleSimController>());
  rclcpp::shutdown();
  printf("hello world challenge package\n");
  return 0;
}
