from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='challenge',
            executable='solution',
            name='sine'
        ),
        Node(
            package='turtlesim',
            executable='turtlesim_node',
            name='turtle'
        )
    ])