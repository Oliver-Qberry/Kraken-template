#pragma once
#include "main.h"

#include "ADIDigitalIn.cpp"
#include "ADIDigitalOut.cpp"

#include "CONTROLLER.cpp" // may need to adjust

#include "DISTANCE.cpp"
#include "IMU.cpp"
#include "MOTOR.cpp"
#include "ROTATION.cpp"


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