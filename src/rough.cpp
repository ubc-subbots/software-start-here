#include <cstdio>
#include "rclcpp/rclcpp.hpp"
#include "turtlesim/msg/pose.hpp"
#include "turtlesim/srv/spawn.hpp"
#include "geometry_msgs/msg/twist.hpp"

class TurtleSimController : public rclcpp::Node
{
public:
  TurtleSimController()
  : Node("turtle_sim_controller")
  {
    publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 10);
    subscriber_ = this->create_subscription<turtlesim::msg::Pose>("turtle1/pose", 10, std::bind(&TurtleSimController::poseCallback, this, std::placeholders::_1));
    
  }

private:
  void poseCallback(const turtlesim::msg::Pose::SharedPtr msg)
  {
    RCLCPP_INFO(this->get_logger(), "Turtle position: x=%f, y=%f", msg->x, msg->y);
  }

  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
  rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscriber_;
  rclcpp::Client<turtlesim::srv::Spawn>::SharedPtr spawn_client_;
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<TurtleSimController>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}

