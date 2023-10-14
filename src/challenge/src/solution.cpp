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
      double ysine=5*sin(((count_++)*PI/20.0));
      double x=4*sin(((count_++)*PI/160.0));

      if (count_<35) {
        x=-5;
        ysine=0;
      }

      twist.linear.x = x;
      twist.linear.y = ysine;
      twist.linear.z = 0;

      twist.angular.x = 0;
      twist.angular.y = 1;
      twist.angular.z = 0;
  
      RCLCPP_INFO(this->get_logger(), "Publishing: '%f'", ysine);
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

  return 0;
}
