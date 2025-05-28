#pragma once
// kraken api
#include "kt/api.hpp"
// handler for auton
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
// function to initialize the devices connected to the robot. will run when the robot powers on.
void initialize_devices();
// function that allows things to be printed to the brains lcd.
void print_to_lcd_task();
void update_position_task();
void update_position_task_2();