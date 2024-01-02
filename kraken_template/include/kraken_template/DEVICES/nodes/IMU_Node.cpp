#pragma once
#include "main.h"
#include <string>
#include <vector>

class Node_IMU {
    public:
        std::string _name;
        std::vector<pros::Imu> imu;
        bool _reset_on_startup;

        Node_IMU (std::string _name, int _port, bool _reset_on_startup) {
            this->_name = _name;
            pros::Imu new_imu(_port);
            this->imu.clear();
            this->imu.push_back(new_imu);
            this->_reset_on_startup = _reset_on_startup;
        }

        pros::Imu get_imu() {return imu.front();}
};