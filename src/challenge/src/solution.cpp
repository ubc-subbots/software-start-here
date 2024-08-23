#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <cmath>

class MyNode : public rclcpp::Node
{
public:
    MyNode() : Node("solution"), rate_(10) {
        RCLCPP_INFO(this->get_logger(), "Node started!");
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
        timer_ = this->create_wall_timer(
                std::chrono::milliseconds(1000 / rate_),
                std::bind(&MyNode::publish_message, this)
        );
    }

private:
    void publish_message() {
        auto message = geometry_msgs::msg::Twist();
        double t = count_++;
        double y_value = std::cos(t / 2.0) * 5;

        message.linear.x = 1;
        message.linear.y = y_value;
        message.linear.z = 0.0;
        message.angular.x = 0.0;
        message.angular.y = 0.0;
        message.angular.z = 0.0;

        RCLCPP_INFO(this->get_logger(), "Publishing: y_value = %f", y_value);
        publisher_->publish(message);

        if (count_ >= duration_) {
            rclcpp::shutdown();
        }
    }

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    int rate_;
    int count_ = 0;
    int duration_ = 1000;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MyNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
