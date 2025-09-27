#include <cstdio>
#include "rclcpp/rclcpp.hpp"
#include <geometry_msgs/msg/twist.hpp>
#include <cmath>
#include "turtlesim/srv/teleport_absolute.hpp"

class SineTurtle : public rclcpp::Node {

  public:
  using Twist = geometry_msgs::msg::Twist;
  
  SineTurtle() : Node("sine_turtle"), time(0.0) {
    
    // Publisher for velocity
    publisher = this->create_publisher<Twist>("turtle1/cmd_vel", 10);

    // Timer for sine movement
    timer = this->create_wall_timer(
        std::chrono::milliseconds(111),
        std::bind(&SineTurtle::sine_move, this)
    );

    // Teleport turtle to the left (x=1.0, y=5.5 for vertical center)
    auto client = this->create_client<turtlesim::srv::TeleportAbsolute>("turtle1/teleport_absolute");
    while (!client->wait_for_service(std::chrono::seconds(1))) {
        RCLCPP_INFO(this->get_logger(), "Waiting for teleport service...");
    }

    auto request = std::make_shared<turtlesim::srv::TeleportAbsolute::Request>();
    request->x = 1.0;       // far left
    request->y = 5.5;       // vertical center
    request->theta = 0.0;   // facing right

    client->async_send_request(request);
    
  } 

  private:
  void sine_move() {

    auto twist = Twist();


    twist.linear.x = 0.5;

    double amplitude = 0.5;

    twist.linear.y = amplitude * std::sin(time);

    RCLCPP_INFO(this->get_logger(), "Publish: linear.x: '%f', linear.y: '%f'", twist.linear.x, twist.linear.y);
    publisher->publish(twist);

    time += 0.1;

  } 


  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher;
  rclcpp::TimerBase::SharedPtr timer;
  double time;

};


int main(int argc, char ** argv)
{
 
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SineTurtle>());
  rclcpp::shutdown();

  return 0;
  
}



