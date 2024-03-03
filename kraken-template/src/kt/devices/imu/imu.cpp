#include "kt/devices/imu/imu.hpp"

void kt::IMU::new_imu(std::string name, int port) {
    pros::Imu new_imu(port);
    node_map[name].imu.clear();
    node_map[name].imu.push_back(new_imu);
}

pros::IMU kt::IMU::get_imu(std::string name) {
    return node_map[name].imu.front();
}

void kt::IMU::reset(std::string name) {
    node_map[name].imu.front().reset();
}