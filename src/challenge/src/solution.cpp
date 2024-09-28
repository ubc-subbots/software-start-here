#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <cmath>  // for sine function

class TurtleController : public rclcpp::Node {
    public:
        TurtleController() : Node("solution_node"), time(0.0)
        {
            // Create a publisher to send velocity commands to the turtle
            publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 10);
            // Set a timer to regularly send velocity commands
            timer_ = this->create_wall_timer(std::chrono::milliseconds(100),
                                            std::bind(&TurtleController::move_turtle, this));
        }

    private:
        void move_turtle()
        {
            // Create a Twist message to command linear and angular velocities
            auto message = geometry_msgs::msg::Twist();
            
            // Command the turtle to move forward while oscillating angular velocity in a sine wave
            message.linear.x = 2.0;  // Constant forward speed
            message.angular.z = std::sin(time);  // Angular velocity as a sine wave
            
            // Publish the message
            publisher_->publish(message);
            
            // Increment the time for the sine wave
            time += 0.1;
        }

        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
        rclcpp::TimerBase::SharedPtr timer_;
        double time;
    };

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TurtleController>());
    rclcpp::shutdown();
    return 0;
}
