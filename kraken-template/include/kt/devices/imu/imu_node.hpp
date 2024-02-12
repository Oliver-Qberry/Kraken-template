#pragma once

#include "pros/imu.hpp"

#include <string>
#include <vector>
class imu_node {
    public:
    std::string _name;
    std::vector<pros::IMU> imu;
};