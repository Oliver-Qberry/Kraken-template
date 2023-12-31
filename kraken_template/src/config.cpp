#pragma once
#include "main.h"
#include "kraken_template/_config.cpp"

void config() {
    // ==================== controller setup ==================== //
    devices.controller.set_drive_keybinds(
        pros::E_CONTROLLER_ANALOG_LEFT_X, 
        pros::E_CONTROLLER_ANALOG_RIGHT_Y, 
        false);

    devices.controller.set_sensitivity(1, 1);

    // ==================== drivetrain setup ==================== //
    drivetrain.set_motor_ports({1, 2, 3}, {4, 5, 6}, 
                               pros::E_MOTOR_BRAKE_COAST, false);
    drivetrain.set_rpm(600, 450, 3.25);

    drivetrain.set_imu_port(9);

    // ==================== motor setup ==================== //
    devices.motor._new("intake", 7, pros::E_MOTOR_BRAKE_COAST, false);
    devices.motor.set_motor_keybinds("intake", pros::E_CONTROLLER_DIGITAL_L1, false, 
                                     true, pros::E_CONTROLLER_DIGITAL_L2);
    
    devices.motor._new("launcher", 8, pros::E_MOTOR_BRAKE_COAST, false);
    devices.motor.set_motor_keybinds("launcher", pros::E_CONTROLLER_DIGITAL_A, true);

    // motors pid setup
    devices.motor.set_motor_pid("launcher", 1.0, 0, 0);

    // ==================== sensor setup ==================== //
    devices.distance._new("front", 10);
    devices.rotation._new("rotation", 11);

    // ==================== 3 wire adid setup ==================== //
    devices.ADIDigitalOut._new("wing", 'a');
    devices.ADIDigitalOut.set_keybinds("wing", pros::E_CONTROLLER_DIGITAL_L1);

    devices.ADIDigitalOut._new("lift", 'b');
    devices.ADIDigitalOut.set_keybinds("lift", pros::E_CONTROLLER_DIGITAL_L1);

    devices.ADIDigitalOut._new("arm", 'c');
    devices.ADIDigitalOut.set_keybinds("arm", pros::E_CONTROLLER_DIGITAL_L1);
}