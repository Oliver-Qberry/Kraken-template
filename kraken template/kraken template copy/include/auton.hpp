#pragma once

#include "kt/api.hpp"
#include "kt/auton_handler/auton_handler.hpp"


extern kt::Chassis chassis;
extern kt::AUTONS autons;
extern kt::ADI_DIGITALIN AdiDigitalIn;
extern kt::ADI_DIGITALOUT AdiDigitalOut;

extern kt::Distance distance;

extern kt::IMU imu;

extern kt::Motor motor;

extern kt::Rotation rotation;

void initialize_auton();
void initialize_task();