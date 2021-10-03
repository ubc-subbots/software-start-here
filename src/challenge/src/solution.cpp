#include <cstdio>
#include <ctime>
#include <math.h>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <turtlesim/msg/pose.hpp>

using std::placeholders::_1;
using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */

class solution : public rclcpp::Node
{
  public:
    solution() 
    : Node("solution"), count_(0)
    {
      publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 20);
      timer_ = this->create_wall_timer(
      20ms, std::bind(&solution::timer_callback, this));
    }

  private:
  
    int count_;
    
    void timer_callback()
    {
    count_+=20;
      auto msg = geometry_msgs::msg::Twist();
      msg.linear.y = 5*sin(count_);
      msg.linear.x = 1;
      RCLCPP_INFO(this->get_logger(), "Publishing: '%lf'", msg.linear.x);
      RCLCPP_INFO(this->get_logger(), "Publishing: '%lf'", msg.linear.y);
      publisher_->publish(msg);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<solution>());
  rclcpp::shutdown();
  return 0;
}
