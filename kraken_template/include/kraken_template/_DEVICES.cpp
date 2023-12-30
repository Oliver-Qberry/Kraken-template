#pragma once
#include "main.h"

#include "DEVICES/ADIDigitalIn.cpp"
#include "DEVICES/ADIDigitalOut.cpp"
#include "DEVICES/IMU.cpp"

class DEVICES {
    public:

    _ADIDigitalIn ADIDigitalIn;
    _ADIDigitalOut ADIDigitalOut;
    _IMU imu;
};

