#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <cmath>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "turtlesim/msg/pose.hpp"
#include "std_msgs/msg/string.hpp"

class SineTurtle : public rclcpp::Node
{
  double direction = 1;
  
  public:
    SineTurtle() : Node("sine_wave")
    {
      velocity_publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
      pose_subscriber_ = this->create_subscription<turtlesim::msg::Pose>("/turtle1/pose", 10, std::bind(&SineTurtle::pose_callback, this, std::placeholders::_1));
      timer_ = this->create_wall_timer(std::chrono::nanoseconds (10), std::bind(&SineTurtle::goto_goal, this));
    }

  private:
    void pose_callback(const turtlesim::msg::Pose::SharedPtr pose)
    {
      x1 = pose -> x;
      y1 = pose -> y;
    }

    void goto_goal()
    {
      if (x1 >= 3*M_PI)
      {
          direction = -1;
      }
      else if (x1 <= 0)
      {
        direction = 1;
      }
      
      speed.linear.x = direction/abs(direction) * 1.0;
      speed.linear.y = 1 * cos(x1);
      velocity_publisher_->publish(speed);
    }

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr velocity_publisher_;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr pose_subscriber_;
    rclcpp::TimerBase::SharedPtr timer_;
    geometry_msgs::msg::Twist speed;
    float x1, y1;
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SineTurtle>());
  rclcpp::shutdown();
  return 0;
}