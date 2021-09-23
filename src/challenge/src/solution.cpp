#include <cstdio>
#include <ctime>
#include <math.h>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <turtlesim/msg/pose.hpp>


using std::placeholders::_1;
using namespace std::chrono_literals;

class Solution : public rclcpp::Node
{
  public:

    Solution() : Node("solution"), time_(0)
    {
      publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel",10);
      timer_ = this->create_wall_timer(
        10ms, std::bind(&Solution::timer_callback, this));
    }

  private:

    int time_;

    void timer_callback()
    {
      time_+=50;
      auto msg = geometry_msgs::msg::Twist();
      msg.linear.x = 5;
      msg.linear.y = 10*sin(time_);
      publisher_->publish(msg);
    }

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Solution>());
  rclcpp::shutdown();
  return 0;
}
//colcon build --packages-select challenge
//ros2 run turtlesim turtlesim_node
//ros2 run challenge solution