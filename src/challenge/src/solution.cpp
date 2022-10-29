
#include <cmath>
#include <time.h>
#include "rclcpp/rclcpp.hpp"
#include <geometry_msgs/msg/twist.hpp>
//A publisher node that generates a Sine wave for turtlesim
 using namespace std::chrono_literals;
class MinimalPublisher : public rclcpp::Node
{




  public:
    MinimalPublisher()
    : Node("minimal_publisher")
    {
      publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 50);
      timer_ = this->create_wall_timer(
      500ms, std::bind(&MinimalPublisher::timer_callback, this));
    }
//Computes direction based on current time
//publishes to turtlesim
  private:
    void timer_callback()
    { 
    
    int time_passed = time(0);
	auto message = geometry_msgs::msg::Twist();
  	message.linear.x = 1;
	message.angular.x = 1;
  	message.angular.z = 2.5*cos(time_passed);
      
      
      publisher_->publish(message);
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

