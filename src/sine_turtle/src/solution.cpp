#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "turtlesim/msg/pose.hpp"
#include "std_msgs/msg/string.hpp"

class GoToGoal : public rclcpp::Node
{
  public:
    GoToGoal() : Node("sine_wave")
    {
      velocity_publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
      pose_subscriber_ = this->create_subscription<turtlesim::msg::Pose>("/turtle1/pose", 10, std::bind(&GoToGoal::pose_callback, this, std::placeholders::_1));
      timer_ = this->create_wall_timer(std::chrono::nanoseconds (10), std::bind(&GoToGoal::goto_goal, this));
      GoToGoal::set_goal();
    }

  private:
    void pose_callback(const turtlesim::msg::Pose::SharedPtr pose)
    {
      x1 = pose -> x;
      y1 = pose -> y;
      theta = pose->theta;
    }

    void set_goal()
    {
      RCLCPP_INFO(this->get_logger(), "Set the desired (x2, y2) of the turtle...");
      std::cout << "Enter desired x location: ";
      std::cin >> x2;
      std::cout << "Enter desired y location: ";
      std::cin >> y2;
    }

    void goto_goal()
    {
      dist_x = x2 - x1;
      dist_y = y2 - y1;
      euclidean_distance = sqrt(pow(dist_x, 2) + pow(dist_y, 2));
      distance_tolerance = 0.5;

      if (euclidean_distance > distance_tolerance)
      {
        float K_linear = 2;
        float K_angular = 4;
        speed.linear.x = K_linear * euclidean_distance;

        angle = atan2(dist_y, dist_x);
        angle_diff = (angle - theta);

        if (angle_diff > M_PI)
        {
          angle_diff -= 2 * M_PI;
        }
        else if (angle_diff < -M_PI)
        {
          angle_diff += 2* M_PI;
        }

        speed.angular.z = angle_diff * K_angular;
      }
      else
      {
        speed.linear.x = 0.0;
        speed.angular.z = 0.0;
        RCLCPP_INFO(this->get_logger(), "Goal (%.2f, %.2f) reached!!!", x2, y2);
        timer_->cancel();
      }
      velocity_publisher_->publish(speed);
    }

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr velocity_publisher_;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr pose_subscriber_;
    rclcpp::TimerBase::SharedPtr timer_;
    geometry_msgs::msg::Twist speed;
    float x1, y1, x2, y2, theta, dist_x, dist_y;
    float euclidean_distance, distance_tolerance, angle, angle_diff;
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<GoToGoal>());
  rclcpp::shutdown();
  return 0;
}