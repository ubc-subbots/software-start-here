#include <cstdio>
#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <geometry_msgs/msg/twist.hpp>

using namespace std::chrono_literals;

class Solution : public rclcpp::Node
{
  public:
    std::shared_ptr<rclcpp::Publisher<geometry_msgs::msg::Twist, std::allocator<void>>> publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    double_t count_;
    Solution()
    : Node("solution"), count_(0.0)
    {
      publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel",10);
      timer_ = this->create_wall_timer(
      500ms, std::bind(&Solution::timer_callback, this));
    }

    private: 
    void timer_callback() {
      auto vel = geometry_msgs::msg::Twist();
      count_ += 0.5;
      double new_y = sin(count_);

      vel.linear.x = 1;
      vel.linear.set__y(new_y);
      publisher_->publish(vel);
    }
};

int main(int argc, char ** argv)
{
  (void) argc;
  (void) argv;

  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Solution>());
  rclcpp::shutdown();
  return 0;
}
