#pragma once

#include "kt/devices/imu/imu_node.hpp"
#include "pros/imu.hpp"
#include <string>
#include <unordered_map>

namespace kt {
class IMU {
    private:
    std::unordered_map<std::string, imu_node> node_map;
    public:

    void new_imu(std::string name, int port) {
        pros::Imu new_imu(port);
        node_map[name].imu.clear();
        node_map[name].imu.push_back(new_imu);
    }

    pros::IMU get_imu(std::string name) {
        return node_map[name].imu.front();
    }

    void reset(std::string name) {
        node_map[name].imu.front().reset();
    }
};
}