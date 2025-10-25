#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <cmath>

class SineWaveTurtle : public rclcpp::Node
{
public:
    SineWaveTurtle() : Node("sine_wave_turtle"), time_(0.0)
    {
        // Create publisher for velocity commands
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>(
            "/turtle1/cmd_vel", 10);
        
        // Create timer that calls timer_callback every 50ms
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(50),
            std::bind(&SineWaveTurtle::timer_callback, this));
        
        RCLCPP_INFO(this->get_logger(), "Sine wave turtle controller started!");
    }

private:
    void timer_callback()
    {
        auto message = geometry_msgs::msg::Twist();
        
        // Linear velocity (constant forward motion)
        message.linear.x = 2.0;
        message.linear.y = 5*std::sin(10*time_);
        message.linear.z = 0.0;
        
        // Publish the message
        publisher_->publish(message);
        
        // Increment time
        time_ += 0.05;  // Matches the 50ms timer period
    }

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    double time_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SineWaveTurtle>());
    rclcpp::shutdown();
    return 0;
}
