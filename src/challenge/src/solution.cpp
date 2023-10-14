#include <cstdio>
#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <cmath>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"

using namespace std::chrono_literals;


#define PI 3.1415926535

class Publisher : public rclcpp::Node
{
  public:
    Publisher()
    : Node ("turtle_controller"),count_(0)
    {
      publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 1);
      timer_ = this->create_wall_timer(
      50ms, std::bind(&Publisher::timer_callback, this));
    }

  private:
    void timer_callback()
    {
      double sine=3*sin(((count_++)*PI/20.0));

      twist.linear.x = 3;
      twist.linear.y = sine;
      twist.linear.z = 0;

      twist.angular.x = 0;
      twist.angular.y = 1;
      twist.angular.z = 0;
  
      RCLCPP_INFO(this->get_logger(), "Publishing: '%f'", sine);
      publisher_->publish(twist);
    }


    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    size_t count_;
    geometry_msgs::msg::Twist twist;

};


int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Publisher>());
  rclcpp::shutdown();

  printf("hello world challenge package\n");
  return 0;
}
