#include <cstdio>
#include "rclcpp/rclcpp.hpp"
#include <geometry_msgs/msg/twist.hpp>
#include <cmath>

class SineTurtle : public rclcpp::Node {

  public:
  using Twist = geometry_msgs::msg::Twist;
  
  SineTurtle() : Node("sine_turtle"), time(0.0) {
    
    
    publisher = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 10);
    timer = this->create_wall_timer(std::chrono::milliseconds(111), std::bind(&SineTurtle::sine_move, this));
    
  } 

  private:
  void sine_move() {

    auto twist = Twist();


    twist.linear.x = 1.0;
    twist.linear.y = std::sin(time);


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



