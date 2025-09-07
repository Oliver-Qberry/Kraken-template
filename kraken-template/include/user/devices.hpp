#pragma once

// kraken api
#include "kt/api.hpp"

namespace kt::devices
{
    // chassis extern def
    extern kt::Chassis chassis;
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

    void initialize_devices();

    // MAYBE WE will see where these go
    //  function that allows things to be printed to the brains lcd.
    void print_to_lcd_task();

    void print_to_controller_task();

    void chassis_setup();

} // namespace kt::devices
