#pragma once

#include "kt/api.hpp"

extern kt::ADI_DIGITALIN AdiDigitalIn;
extern kt::ADI_DIGITALOUT AdiDigitalOut;

extern kt::Distance distance;
extern kt::IMU imu;

extern kt::Motor motor;

extern kt::Rotation rotation;

void initialize_devices();