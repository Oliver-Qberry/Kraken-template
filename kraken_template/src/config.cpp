#pragma once
#include "main.h"
#include "kraken_template/_config.cpp"

using namespace pros;

void config() {
    // ==================== controller setup ==================== //
    devices.controller.set_drive_keybinds(
        E_CONTROLLER_ANALOG_LEFT_X, 
        E_CONTROLLER_ANALOG_RIGHT_Y, 
        false);

    devices.controller.set_sensitivity(1, 1);

    // ==================== drivetrain setup ==================== //
    drivetrain.set_motor_ports({1, 2, 3}, {4, 5, 6}, 
                               E_MOTOR_BRAKE_COAST, false);
    drivetrain.set_rpm(600, 450, 3.25);

    drivetrain.set_imu_port(9);

    // ==================== motor setup ==================== //
    devices.motor.new_motor("intake", 7, E_MOTOR_BRAKE_COAST, false);
    devices.motor.set_motor_keybinds("intake", E_CONTROLLER_DIGITAL_L1, false, 
                                     true, E_CONTROLLER_DIGITAL_L2);
    
    devices.motor.new_motor("launcher", 8, E_MOTOR_BRAKE_COAST, false);
    devices.motor.set_motor_keybinds("launcher", E_CONTROLLER_DIGITAL_A, true);

    // motors pid setup
    devices.motor.set_pid_values("launcher", 1.0, 0, 0);
    devices.motor.set_pid_target_velocity("launcher", 500, 10, 600);

    // ==================== sensor setup ==================== //
    devices.distance.new_distance("front", 10);
    devices.rotation.new_rotation("rotation", 11);

    // ==================== 3 wire adid setup ==================== //
    devices.ADIDigitalOut.new_ADI("wing", 'a');
    devices.ADIDigitalOut.set_ADI_keybinds("wing", E_CONTROLLER_DIGITAL_L1);

    devices.ADIDigitalOut.new_ADI("lift", 'b');
    devices.ADIDigitalOut.set_ADI_keybinds("lift", E_CONTROLLER_DIGITAL_L1);

    devices.ADIDigitalOut.new_ADI("arm", 'c');
    devices.ADIDigitalOut.set_ADI_keybinds("arm", E_CONTROLLER_DIGITAL_L1);

    
}