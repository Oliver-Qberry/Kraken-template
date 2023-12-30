#pragma once
#include "main.h"
#include "kraken_template/_config.cpp"

void config() {


    // ==================== controller setup ==================== //
    //devices.controller.set_drive_keybinds(pros::controller_analog_e_t::E_CONTROLLER_ANALOG_LEFT_X, 
                                          //pros::controller_analog_e_t::E_CONTROLLER_ANALOG_LEFT_Y, 
                                          //false);
    // way to lower turn and drive speed
    // ==================== drivetrain setup ==================== //


    

    // ==================== motor setup ==================== //
    //devices.motor.new_motor("intake", 7, pros::E_MOTOR_BRAKE_COAST, false);
    //devices.motor.set_motor_keybinds("intake", pros::E_CONTROLLER_DIGITAL_L1, false, 
                                     //true, pros::E_CONTROLLER_DIGITAL_L2);
    
    //devices.motor.new_motor("launcher", 8, pros::E_MOTOR_BRAKE_COAST, false);
    //devices.motor.set_motor_keybinds("launcher", pros::E_CONTROLLER_DIGITAL_A, true);
    //devices.motor.set_motor_pid("launcher");

    // ==================== sensor setup ==================== //
    //devices.sensor.new_imu("imu", 9, true);

    // distance
    // rotation

    // ==================== 3 wire adid setup ==================== //
    devices.ADIDigitalOut._new("wing", 'a');
    devices.ADIDigitalOut.set_keybinds("wing", pros::E_CONTROLLER_DIGITAL_L1);

    devices.ADIDigitalOut._new("lift", 'b');
    devices.ADIDigitalOut.set_keybinds("lift", pros::E_CONTROLLER_DIGITAL_L1);

    devices.ADIDigitalOut._new("arm", 'c');
    devices.ADIDigitalOut.set_keybinds("arm", pros::E_CONTROLLER_DIGITAL_L1);
}