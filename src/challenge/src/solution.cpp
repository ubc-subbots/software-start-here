#include "rclcpp/rclcpp.hpp"

class MyNode : public rclcpp::Node
{
public:
   MyNode() : Node("solution") {
      RCLCPP_INFO(get_logger(), "Node started!");
   }
private:
};

int main(int argc, char **argv)
{
   rclcpp::init(argc, argv);
   auto node = std::make_shared<MyNode>();
   rclcpp::spin(node);
   rclcpp::shutdown();
   return 0;
}
