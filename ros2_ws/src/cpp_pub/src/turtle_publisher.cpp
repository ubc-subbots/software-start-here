#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <cmath>
#include <thread>
#include <mutex>
#include <termios.h>
#include <unistd.h>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "turtlesim/msg/pose.hpp"
#include "turtlesim/srv/teleport_absolute.hpp"
#include "std_srvs/srv/empty.hpp"

using namespace std::chrono_literals;

class TurtlePublisher : public rclcpp::Node
{
public:
    TurtlePublisher()
    : Node("turtle_publisher"), time_(0.0)
    {
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);

        subscription_ = this->create_subscription<turtlesim::msg::Pose>(
            "/turtle1/pose", 10,
            std::bind(&TurtlePublisher::pose_callback, this, std::placeholders::_1));

        teleport_client_ = this->create_client<turtlesim::srv::TeleportAbsolute>("/turtle1/teleport_absolute");
        clear_client_ = this->create_client<std_srvs::srv::Empty>("/clear");

        std::thread([this]() { this->keyboard_loop(); }).detach();

        timer_ = this->create_wall_timer(
            100ms, std::bind(&TurtlePublisher::timer_callback, this));
    }

private:
    void pose_callback(const turtlesim::msg::Pose::SharedPtr msg)
    {
        std::lock_guard<std::mutex> lock(pose_mutex_);
        current_pose_ = *msg;
    }

    void keyboard_loop()
    {
        struct termios old_tio, new_tio;
        tcgetattr(STDIN_FILENO, &old_tio);
        new_tio = old_tio;
        new_tio.c_lflag &= (~ICANON & ~ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);

        RCLCPP_INFO(this->get_logger(), "Press SPACE to reset turtle position and clear screen.");

        while (rclcpp::ok())
        {
            char c = getchar();
            if (c == ' ')
            {
                RCLCPP_INFO(this->get_logger(), "Spacebar pressed — resetting turtle!");
                reset_turtle();
            }
        }

        tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
    }

    void reset_turtle()
    {
      if (!teleport_client_->wait_for_service(1s) || !clear_client_->wait_for_service(1s))
      {
          RCLCPP_WARN(this->get_logger(), "Services not available");
          return;
      }

      // Teleport turtle to center
      auto teleport_req = std::make_shared<turtlesim::srv::TeleportAbsolute::Request>();
      teleport_req->x = 0;
      teleport_req->y = 5.5;
      teleport_req->theta = 0.0;
      teleport_client_->async_send_request(teleport_req);

      // Clear background
      auto clear_req = std::make_shared<std_srvs::srv::Empty::Request>();
      clear_client_->async_send_request(clear_req);

      RCLCPP_INFO(this->get_logger(), "Turtle reset and screen cleared (async).");
    }


    void timer_callback()
    {
        auto message = geometry_msgs::msg::Twist();

        message.linear.x = 0.7;
        message.angular.z = std::sin(time_);

        {
            std::lock_guard<std::mutex> lock(pose_mutex_);
            RCLCPP_INFO(this->get_logger(),
                        "x=%.2f y=%.2f θ=%.2f | Publishing linear.x=%.2f angular.z=%.2f",
                        current_pose_.x, current_pose_.y, current_pose_.theta,
                        message.linear.x, message.angular.z);
        }

        publisher_->publish(message);

        time_ += 0.1; // smaller increment for smooth motion
    }

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscription_;
    rclcpp::TimerBase::SharedPtr timer_;

    rclcpp::Client<turtlesim::srv::TeleportAbsolute>::SharedPtr teleport_client_;
    rclcpp::Client<std_srvs::srv::Empty>::SharedPtr clear_client_;

    turtlesim::msg::Pose current_pose_;
    double time_;
    std::mutex pose_mutex_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TurtlePublisher>());
    rclcpp::shutdown();
    return 0;
}
