#pragma once

#include <unistd.h> // Used by sleep
#include "rclcpp/rclcpp.hpp"
#include "std_srvs/srv/empty.hpp"
#include <behaviortree_cpp_v3/action_node.h>

class SnapshotClient : public BT::SyncActionNode
{
    public:
        SnapshotClient(const std::string& name, const BT::NodeConfiguration& config)
            : BT::SyncActionNode(name, config)
        {
            node_ = rclcpp::Node::make_shared("snapshot_client");
            client_ = node_->create_client<std_srvs::srv::Empty>("save");
        }

        static BT::PortsList providedPorts()
        {
            return{ BT::InputPort<std::string>("event") };
        }

        virtual BT::NodeStatus tick() override
        {
            // Waiting for service /save
            while (!client_->wait_for_service(std::chrono::seconds(1))) {
                if (!rclcpp::ok()) {
                    RCLCPP_ERROR(node_->get_logger(), "Interrupted while waiting for service /save.");
                    return BT::NodeStatus::FAILURE;
                }
                RCLCPP_INFO(node_->get_logger(), "Waiting for service /save to appear...");
            }
            sleep(3); // To stablize the camera
            auto request = std::make_shared<std_srvs::srv::Empty::Request>();
            auto result_future = client_->async_send_request(request);
            if (rclcpp::spin_until_future_complete(node_, result_future) != rclcpp::FutureReturnCode::SUCCESS)
            {
                RCLCPP_ERROR(node_->get_logger(), "Unable to call /save");
                return BT::NodeStatus::FAILURE;
            }
            sleep(1); // To stablize the camera
            return BT::NodeStatus::SUCCESS;
        }

    private:
        rclcpp::Node::SharedPtr node_;
        rclcpp::Client<std_srvs::srv::Empty>::SharedPtr client_;
};