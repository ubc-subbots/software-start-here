#include <chrono>
#include <cmath>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "turtlesim/srv/teleport_absolute.hpp"
#include "turtlesim/srv/set_pen.hpp"

using namespace std::chrono_literals;

class TurtleSineNode : public rclcpp::Node
{
public:
  TurtleSineNode()
  : Node("turtle_sine_node"), t_(0.0), x_(1.0), y_center_(5.5), amplitude_(2.0), x_max_(11.0)
  {
    twist_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 10);
    teleport_client_ = this->create_client<turtlesim::srv::TeleportAbsolute>("turtle1/teleport_absolute");
    pen_client_ = this->create_client<turtlesim::srv::SetPen>("turtle1/set_pen");

    spawn_turtle();

    // 20 Hz timer
    timer_ = this->create_wall_timer(50ms, std::bind(&TurtleSineNode::timer_callback, this));

    RCLCPP_INFO(this->get_logger(), "🐢 Perfect left-to-right sine wave node started!");
  }

private:
  void spawn_turtle()
  {
    auto pen_req = std::make_shared<turtlesim::srv::SetPen::Request>();
    pen_req->off = true;  // disables drawing
    if (pen_client_->wait_for_service(1s)) {
      pen_client_->async_send_request(pen_req);
    }

    auto teleport_req = std::make_shared<turtlesim::srv::TeleportAbsolute::Request>();
    teleport_req->x = 1.0;
    teleport_req->y = y_center_;
    teleport_req->theta = -M_PI_4;  // facing southeast (down-right)
    if (teleport_client_->wait_for_service(1s)) {
      teleport_client_->async_send_request(teleport_req);
    }

    RCLCPP_INFO(this->get_logger(), "✏️ Pen turned off permanently.");

    // Reset state
    x_ = 1.0;
    t_ = 0.0;
  }

  void timer_callback()
  {
    if (x_ >= x_max_ - 4.5)
    {
      spawn_turtle();
      return;
    }

    geometry_msgs::msg::Twist msg;
    msg.linear.x = 2.0;
    msg.angular.z = 1.5 * sin(t_);
    twist_pub_->publish(msg);

    x_ += 0.05;
    t_ += 0.1;
  }

  // ROS interfaces
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr twist_pub_;
  rclcpp::Client<turtlesim::srv::TeleportAbsolute>::SharedPtr teleport_client_;
  rclcpp::Client<turtlesim::srv::SetPen>::SharedPtr pen_client_;
  rclcpp::TimerBase::SharedPtr timer_;

  // Motion parameters
  double t_;         // sine phase
  double x_;         // simulated horizontal position
  double y_center_;  // vertical center
  double amplitude_; // sine amplitude
  double x_max_;     // right boundary
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TurtleSineNode>());
  rclcpp::shutdown();
  return 0;
}
