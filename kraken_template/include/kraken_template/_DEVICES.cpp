#pragma once
#include "main.h"

#include "DEVICES/ADIDigitalIn.cpp"
#include "DEVICES/ADIDigitalOut.cpp"

#include "DEVICES/CONTROLLER.cpp" // may need to adjust

#include "DEVICES/DISTANCE.cpp"
#include "DEVICES/IMU.cpp"
#include "DEVICES/MOTOR.cpp"
#include "DEVICES/ROTATION.cpp"


class DEVICES {
    public:
    _ADIDigitalIn ADIDigitalIn;
    _ADIDigitalOut ADIDigitalOut;
    _CONTROLLER controller;
    _IMU imu;
    _MOTOR motor;
    _DISTANCE distance;
    _ROTATION rotation;
};