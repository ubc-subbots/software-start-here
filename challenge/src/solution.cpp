#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <geometry_msgs/msg/twist.hpp>
#include <cmath>

#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */

class Solution : public rclcpp::Node
{
  public:
    Solution(): Node("sine_wave"), count_(0)
    {
      publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
      timer_ = this->create_wall_timer(500ms, std::bind(&Solution::timer_callback, this));
    }

  private:
  int angle = 0.5;
    void timer_callback()
    {
      geometry_msgs::msg::Twist twist;  
      twist.linear.y= cos(angle); 
      twist.linear.x = 0.5;
      publisher_->publish(twist);
      angle ++;
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Solution>());
  rclcpp::shutdown();
  return 0;
}
