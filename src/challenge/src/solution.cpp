// Include important C++ header files that provide class
// templates for useful operations.
#include <chrono> // Date and time
#include <functional> // Arithmetic, comparisons, and logical operations
#include <memory> // Dynamic memory management
#include <math.h>
#include <ctime>

# define M_PI           3.14159265358979323846
 
// ROS Client Library for C++
// Allows use of the most common elements of ROS 2
#include "rclcpp/rclcpp.hpp"
 
// Built-in message type that will be used to publish data
#include <geometry_msgs/msg/twist.hpp>
 
// chrono_literals handles user-defined time durations (e.g. 500ms) 
using namespace std::chrono_literals;
 
// Create the node class named Solution which inherits the attributes
// and methods of the rclcpp::Node class.
class Solution  : public rclcpp::Node
{
  public:
    // Constructor creates a node named solution. 
    // The published message count is initialized to 0.
    Solution()
    : Node("solution"), count_(0)
    {
      // Publisher publishes Twist data type messages to a topic named "/turtle1/cmd_vel". 
      // The size of the queue is 10 messages.
      publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel",10);
       
      // Initialize the timer. The timer_callback function will execute every
      // 10 milliseconds.
      timer_ = this->create_wall_timer(
      100ms, std::bind(&Solution::timer_callback, this)); 
    }
 
  private:

  int time_; //making variable to keep track of time passing 

    // This method executes every 10 milliseconds
    void timer_callback()
    {
      // Create a new message of type Twist
      auto message = geometry_msgs::msg::Twist();

      time_ += 100; //captures every 10 milliseconds
       
      // Set parameters for each member of the structure type
      message.linear.x = 1;
      message.linear.y = 10*sin(time_ + M_PI/2);
 
      // Print every message to the terminal window      
      RCLCPP_INFO(this->get_logger(),"Publishing: '%lf'", message.linear.x);
      RCLCPP_INFO(this->get_logger(),"Publishing: '%lf'", message.linear.y);
       
      // Publish the message to the topic named "/turtle1/cmd_vel"
      publisher_->publish(message);
    }
     
    // Declaration of the timer_ attribute
    rclcpp::TimerBase::SharedPtr timer_;
  
    // Declaration of the publisher_ attribute
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
   
    // Declaration of the count_ attribute
    size_t count_;
};
 
// Node execution starts here
int main(int argc, char * argv[])
{
  // Initialize ROS 2
  rclcpp::init(argc, argv);
  
  // Start processing data from the node as well as the callbacks and the timer
  rclcpp::spin(std::make_shared<Solution>());
 
  // Shutdown the node when finished
  rclcpp::shutdown();
  return 0;
}