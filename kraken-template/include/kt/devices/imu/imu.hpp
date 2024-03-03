#pragma once

#include "kt/devices/imu/imu_node.hpp"
#include "pros/imu.hpp"

#include <string>
#include <unordered_map>

namespace kt {
// class for handling the imu sensor
class IMU {
    private:
    // imu sensor node map
    std::unordered_map<std::string, imu_node> node_map;

    public:
    // adds a new imu node to the handler.
    /*
    parameters:
        name.
        port.
    */
    void new_imu(std::string name, int port);

    // gets the imu sensor by its name
    pros::IMU get_imu(std::string name);

    // resets an imu by its name
    void reset(std::string name);
};
}