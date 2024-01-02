#pragma once
#include "main.h"

#include "nodes/IMU_Node.cpp"
#include <string>


class _IMU {
    private:
        std::vector<std::string> node_names;
        std::unordered_map<std::string, Node_IMU> node_map;
        
    public:
        bool added_imu = false;

        void new_IMU(std::string name, int port, bool reset_on_startup = true) {

        }

        pros::Imu get_IMU(std::string name) {
            return node_map[name].get_imu();
        }

        std::vector<std::string> get_IMU_names() {
            return node_names;
        }

        Node_IMU get_IMU_node(std::string name) {
            return node_map[name];
        }
};