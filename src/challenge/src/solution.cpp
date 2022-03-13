#include <cstdio>
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
      publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 10);
      timer_ = this->create_wall_timer(
      100ms, std::bind(&MinimalPublisher::timer_callback, this));
    }

  private:
    int count_;
    void timer_callback()
    {
      auto message = geometry_msgs::msg::Twist();
      message.linear.x = 2;
      message.linear.y = 5*sin(count_);
      publisher_->publish(message);
      count_++;
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
   
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
