#include <chrono>
#include <time.h>
#include <math.h>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "turtlesim/msg/pose.hpp"

using namespace std::chrono_literals;

class MinimalPublisher : public rclcpp::Node {

public:
  MinimalPublisher()
      : Node("solution"), count_(0)
  {
    publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 10);

    /* Setting up timer */
    timer_ = this->create_wall_timer(
        100ms, std::bind(&MinimalPublisher::timer_callback, this));

  }

private:

  int count_;

  void timer_callback() {
    
    if (count_ < 50) {

      auto velocity = geometry_msgs::msg::Twist();

      velocity.linear.x = (0.5);
      velocity.linear.y = (sin(count_));

      publisher_->publish(velocity);
      count_++;

    }

  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}