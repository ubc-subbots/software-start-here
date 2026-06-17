#include <chrono>
#include <cmath>
#include "rclcpp/rclcpp.hpp"
#include "turtlesim/msg/pose.hpp"
#include "turtlesim/srv/teleport_absolute.hpp"
#include "geometry_msgs/msg/twist.hpp"

using namespace std::chrono_literals;

class SinePlotter : public rclcpp::Node
{
public:
    SinePlotter() : Node("solution_node"), t_(0.0)
    {
        client_ = this->create_client<turtlesim::srv::TeleportAbsolute>("/turtle1/teleport_absolute");

        // wait for teleport service
        while(!client_->wait_for_service(1s)) {
            RCLCPP_INFO(this->get_logger(), "Waiting for turtlesim...");
        }

        timer_ = this->create_wall_timer(20ms, std::bind(&SinePlotter::plot_callback, this));
    }

private:
    void plot_callback()
    {
        double x0 = 5.5;   // center of screen (midpoint)
        double y0 = 5.5;   // vertical starting point
        double amplitude = 3.0; // height of sine wave
        double speed = 0.05;    // how fast to move across x-axis
        double frequency = 2.0; // sine wave frequency

        double x = x0 + t_;
        double y = y0 + amplitude * std::sin(frequency * t_);
        double theta = 0.0; // orientation doesn't matter

        auto request = std::make_shared<turtlesim::srv::TeleportAbsolute::Request>();
        request->x = x;
        request->y = y;
        request->theta = theta;
        client_->async_send_request(request);

        t_ += speed;
    }

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Client<turtlesim::srv::TeleportAbsolute>::SharedPtr client_;
    double t_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SinePlotter>());
    rclcpp::shutdown();
    return 0;
}

