#pragma once

#include "pros/imu.hpp"

#include <string>
#include <vector>

// imu sensor node
class imu_node {
    public:
    // nodes name
    std::string _name;
    // nodes imu sensor
    std::vector<pros::IMU> imu;
};