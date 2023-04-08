
#include <ctime>
#include <math.h>
#include "rclcpp/rclcpp.hpp"
#include <geometry_msgs/msg/twist.hpp>

using namespace std::chrono_literals;

class SineWave : public rclcpp::Node
{
public:
SineWave()
: Node("SineWave")
{
publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
timer_ = this->create_wall_timer(
500ms, std::bind(&SineWave::timer_callback, this));
x_ =0.0;
}

private:
void timer_callback()
{

auto msg = geometry_msgs::msg::Twist();
msg.linear.x = 1.0*sin(this->x_);
msg.linear.y = 1.0;
msg.angular.z = 0.0;
publisher_->publish(msg);
this-> x_++;
}
rclcpp::TimerBase::SharedPtr timer_;
rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
double x_;
};

int main(int argc, char * argv[])
{
rclcpp::init(argc, argv);
rclcpp::spin(std::make_shared<SineWave>());
rclcpp::shutdown();
return 0;
}