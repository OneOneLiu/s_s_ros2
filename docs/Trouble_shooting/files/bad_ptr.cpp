// 这是会报错的版本
#include "rclcpp/rclcpp.hpp"
#include "ur5_robot_gripper/srv/move_to_cartesian_position.hpp"
#include "ur5_robot_gripper/robot_control.hpp"

class RobotServiceNode : public rclcpp::Node
{
public:
    RobotServiceNode()
    : Node("robot_service_node")
    {
        RCLCPP_INFO(this->get_logger(), "Initializing RobotServiceNode...");

        move_to_cartesian_position_service_ = this->create_service<ur5_robot_gripper::srv::MoveToCartesianPosition>(
            "move_to_cartesian_position", std::bind(&RobotServiceNode::moveToCartesianPositionCallback, this, std::placeholders::_1, std::placeholders::_2));
        RCLCPP_INFO(this->get_logger(), "Service 'move_to_cartesian_position' is ready.");

        // 初始化 RobotMover
        robot_mover_ = std::make_shared<RobotMover>(shared_from_this());
        RCLCPP_INFO(this->get_logger(), "RobotMover initialized.");
    }

private:
    void moveToCartesianPositionCallback(const std::shared_ptr<ur5_robot_gripper::srv::MoveToCartesianPosition::Request> request,
                                         std::shared_ptr<ur5_robot_gripper::srv::MoveToCartesianPosition::Response> response)
    {
        RCLCPP_INFO(this->get_logger(), "Received request to move to position: x=%.3f, y=%.3f, z=%.3f",
                    request->px, request->py, request->pz);
        robot_mover_->moveToCartesianPosition(request->px, request->py, request->pz);
        response->success = true;
    }

    rclcpp::Service<ur5_robot_gripper::srv::MoveToCartesianPosition>::SharedPtr move_to_cartesian_position_service_;
    std::shared_ptr<RobotMover> robot_mover_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Initializing RobotServiceNode...");
    auto node = std::make_shared<RobotServiceNode>();
    RCLCPP_INFO(node->get_logger(), "RobotServiceNode has started and is ready.");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

// 这是正常运行的版本
#include "rclcpp/rclcpp.hpp"
#include "ur5_robot_gripper/srv/move_to_cartesian_position.hpp"
#include "ur5_robot_gripper/robot_control.hpp"

class RobotServiceNode : public rclcpp::Node
{
public:
    RobotServiceNode()
    : Node("robot_service_node")
    {
        RCLCPP_INFO(this->get_logger(), "Initializing RobotServiceNode...");

        move_to_cartesian_position_service_ = this->create_service<ur5_robot_gripper::srv::MoveToCartesianPosition>(
            "move_to_cartesian_position", std::bind(&RobotServiceNode::moveToCartesianPositionCallback, this, std::placeholders::_1, std::placeholders::_2));
        RCLCPP_INFO(this->get_logger(), "Service 'move_to_cartesian_position' is ready.");
    }

    void initializeRobotMover()
    {
        // 在构造函数外部初始化 RobotMover
        robot_mover_ = std::make_shared<RobotMover>(shared_from_this());
        RCLCPP_INFO(this->get_logger(), "RobotMover initialized.");
    }

private:
    void moveToCartesianPositionCallback(const std::shared_ptr<ur5_robot_gripper::srv::MoveToCartesianPosition::Request> request,
                                         std::shared_ptr<ur5_robot_gripper::srv::MoveToCartesianPosition::Response> response)
    {
        RCLCPP_INFO(this->get_logger(), "Received request to move to position: x=%.3f, y=%.3f, z=%.3f",
                    request->px, request->py, request->pz);
        robot_mover_->moveToCartesianPosition(request->px, request->py, request->pz);
        response->success = true;
    }

    rclcpp::Service<ur5_robot_gripper::srv::MoveToCartesianPosition>::SharedPtr move_to_cartesian_position_service_;
    std::shared_ptr<RobotMover> robot_mover_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Initializing RobotServiceNode...");
    auto node = std::make_shared<RobotServiceNode>();
    node->initializeRobotMover();  // 在节点初始化后再初始化 RobotMover
    RCLCPP_INFO(node->get_logger(), "RobotServiceNode has started and is ready.");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
