#pragma once

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <behaviortree_cpp_v3/action_node.h>

static std::string interrupt_event;

void interruptCallback(const std_msgs::msg::String::SharedPtr msg)
{
    printf("interrupt callback detect event: %s\n", msg->data.c_str());
    interrupt_event = msg->data;
}

class InterruptEvent : public BT::SyncActionNode
{
    public:
        InterruptEvent(const std::string& name, const BT::NodeConfiguration& config)
            : BT::SyncActionNode(name, config)
        {
            node_ = rclcpp::Node::make_shared("interupt_event");
            sub_ = node_->create_subscription<std_msgs::msg::String>("interrupt_event", 1000, interruptCallback);
        }

        static BT::PortsList providedPorts()
        {
            return{ BT::InputPort<std::string>("event") };
        }

        virtual BT::NodeStatus tick() override
        {
            std::string expect_event;

            printf("Checking interrupt....\n");
            if (!getInput<std::string>("event", expect_event)) {
                throw BT::RuntimeError("missing required input [event]");
            }

            interrupt_event = "";
            rclcpp::spin_some(node_);

            if (interrupt_event == expect_event)
                return BT::NodeStatus::FAILURE;
            else
                return BT::NodeStatus::SUCCESS;
        }

    private:
        rclcpp::Node::SharedPtr node_;
        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;
};