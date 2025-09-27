#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/Twist.hpp"


using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */

class MinimalPublisher : public rclcpp::Node
{
  public:
    MinimalPublisher()
    : Node("minimal_publisher")
    {
      publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 10);

      /* Setting up timer */
      timer_ = this->create_wall_timer(
      500ms, std::bind(&MinimalPublisher::timer_callback, this));
    }

  private:
    void timer_callback()
    /* Where data actually gets published */
    {
        auto position = geometry_msgs::msg::Twist();
        auto start = std::chrono::system_clock::now();

        // position.linear.x = std::chrono::duration<double>(start - std::chrono::system_clock::now());
        // position.linear.y = std::chrono::duration<double>(1);

        position.linear.x = 1;
        position.linear.y = 1;

        publisher_->publish(position);
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