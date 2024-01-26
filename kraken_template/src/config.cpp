#pragma once
#include "main.h"
#include "kraken_template/_config.cpp"
#include "pros/llemu.hpp"
using namespace std;

// classes
// ktv, devices, drivetrain, AUTO
// opc and AUTO used in main

/*
// ==================== how to use the config file / functions ==================== //

// ==================== how to use the pros/pvc variables ==================== //

// ==================== what are sensor functions ==================== //

// ==================== how to setup the config function ==================== //

// ==================== how to setup the auto config function ==================== //

// ==================== the setup on startup function ==================== //

*/

// ==================== place your sensor functions here ==================== //

void example_sensor_function() {
    cout<<"sensor function called"<<endl;
}
// ==================== auto config function ==================== //

void example_auto_function_1() {
    cout<<"example auto function 1 is running"<<endl;
}

// ==================== device config function ==================== //
void config() {
    // ==================== controller setup ==================== //
    devices.controller.set_drive_keybinds(pvc.controller.left_stick_x, 
                                          pvc.controller.right_stick_y, 
                                          false);
    devices.controller.set_sensitivity(1, 1);

    // ==================== drivetrain setup ==================== //
    drivetrain.set_motor_ports({1, 2, 3}, {4, 5, 6}, pvc.brake.coast);
    drivetrain.set_imu_port(7);
    drivetrain.set_rpm(600, 450, 3.25);

    drivetrain.set_drive_pid(1.0, 0.0, 0.0, 10);
    drivetrain.set_turn_pid(1.0, 0.0, 0.0, 10);

    // ==================== motor setup ==================== //
    devices.motor.new_motor("motor 1", 8, pvc.brake.coast);
    devices.motor.set_motor_keybinds("motor 1", pvc.controller.A);

    // ==================== sensor setup ==================== //


    // ==================== 3 wire adid setup ==================== //
    devices.ADIDigitalOut.new_ADI("out", 'a');
    devices.ADIDigitalOut.set_ADI_keybinds("out", pvc.controller.A);

    devices.ADIDigitalIn.new_ADI("in", 'b');
    devices.ADIDigitalIn.set_ADI_keybinds("in", example_sensor_function, pvc.controller.B);




    // ==================== adding auto functions ==================== //
    AUTO.new_auto("name", "desc", example_auto_function_1);
    AUTO.set_default_auto("name");
    
    AUTO.set_auto_select_keybind(pvc.controller.DOWN);
}

void when_competition_initialize() {}
void when_disabled() {}


/*
below are for setting up the startup functions.
do not change unless you know what you are doing.

the function is called inside initialize() in main.cpp and used to setup
devices when the robot turns on. 
*/
// ==================== setup on startup control function ==================== //
void setup_on_startup() {

    AUTO.generate_name_array();

    pros::lcd::initialize();

    drivetrain.imu().reset();

    

    
    
}