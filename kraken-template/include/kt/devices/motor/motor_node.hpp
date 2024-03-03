#pragma once

#include "kt/pid.hpp"
#include "kt/util.hpp"

#include "pros/adi.h"
#include "pros/misc.h"
#include "pros/motors.hpp"

#include <string>
#include <vector>

// motor node
class motor_node {
    private:
    // pid volts
    double pid_volts_out = 0;

    public:
    // nodes name
    std::string _name;
    // nodes motor
    std::vector<pros::Motor> motor;
    // nodes keybind
    pros::controller_digital_e_t _keybind;
    // nodes press type
    kt::e_press_type _press_type;
    // nodes reverse keybind
    pros::controller_digital_e_t _reverse_keybind;
    // nodes reverse keybind
    kt::e_press_type _reverse_press_type;
    // node has data for opc bool
    bool _has_data_for_opc = false;
    // node has reverse data bool
    bool _has_reverse_data = false;
    // motor pid object
    kt::util::PIDController motor_pid_controller;
    // node has data for pid bool
    bool _has_data_for_pid = false;
    // nodes pid active bool
    bool _pid_on = false;
    // nodes max volts 
    double MAX_VOLTS = 127;
    // nodes motor sensitivity
    double MOTOR_SENSITIVITY = 1;
    // node motor is reversed bool
    bool _motor_reverse = false;
    // nodes motor active bool
    bool _motor_on = false;
    // opcontrol function for motor
    void opcontrol();
}; // end of motor_node class