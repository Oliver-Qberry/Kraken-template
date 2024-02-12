#pragma once

#include "kt/api.hpp"
#include "kt/auton_handler/auton_handler.hpp"

// chassis extern def
extern kt::Chassis chassis;
// autons extern def
extern kt::AUTONS autons;
// AdiDigitalIn extern def
extern kt::ADI_DIGITALIN AdiDigitalIn;
// ADIDigitalOut extern def
extern kt::ADI_DIGITALOUT AdiDigitalOut;
// distance extern def
extern kt::Distance distance;
// imu extern def
extern kt::IMU imu;
// motor extern def
extern kt::Motor motor;
// rotation extern def
extern kt::Rotation rotation;
// function to save auto functions to auton class
void initialize_auton();
void auton_select_task();