#pragma once

#include "kt/pid.hpp"
#include "kt/util.hpp"
#include "pros/adi.h"
#include "pros/misc.h"
#include "pros/motors.hpp"

#include <string>
#include <vector>
class motor_node {
    private:
    double pid_volts_out = 0;
    public:
    std::string _name;
    std::vector<pros::Motor> motor;

    pros::controller_digital_e_t _keybind;
    kt::e_press_type _press_type;

    pros::controller_digital_e_t _reverse_keybind;
    kt::e_press_type _reverse_press_type;

    bool _has_data_for_opc = false;
    bool _has_reverse_data = false;

    kt::util::PIDController motor_pid_controller;

    bool _has_data_for_pid = false;
    bool _pid_on = false;

    double MAX_VOLTS = 127;
    double MOTOR_SENSITIVITY = 1;

    bool _motor_reverse = false;
    bool _motor_on = false;

    void opcontrol() {
        if (_has_data_for_opc) {
            if (_has_data_for_pid) {
                // pid motor opc
                //////////////////////////////////////////
                // adjust to add in keybinds
                //////////////////////////////////////////
                this->pid_volts_out = motor_pid_controller.calculate(motor.front().get_actual_velocity());
                if (pid_volts_out*MOTOR_SENSITIVITY > MAX_VOLTS) {
                    pid_volts_out = MAX_VOLTS;
                }
                if (_pid_on == true) {
                    motor.front().move(pid_volts_out*MOTOR_SENSITIVITY);
                } else {
                    motor.front().brake();
                }
            } else if (_has_reverse_data) {
                // has reverse data motor opc
                if (_press_type == kt::ON_NEW_PRESS && _reverse_press_type == kt::ON_NEW_PRESS) {
                    // both are on new press
                    if (master.get_digital_new_press(_keybind)) {
                        _motor_on = (_motor_on) ? false : true;
                        _motor_reverse = false;
                    }
                    if (master.get_digital_new_press(_reverse_keybind)) {
                        _motor_on = (_motor_on) ? false : true;
                        _motor_reverse = true;
                    }
                    if (_motor_on) {
                        if (_motor_reverse) {
                            motor.front().move(MAX_VOLTS*MOTOR_SENSITIVITY * -1);
                        } else {
                            motor.front().move(MAX_VOLTS*MOTOR_SENSITIVITY);
                        }
                    } else {
                        motor.front().brake();
                    }
                } else if (_press_type == kt::ON_NEW_PRESS && _reverse_press_type == kt::ON_PRESS) {
                    // on new press and on press
                    if (master.get_digital(_reverse_keybind)) {
                        _motor_reverse = true;
                    } else {
                        _motor_reverse = false;
                    }
                    if (master.get_digital_new_press(_keybind)) {
                        _motor_on = (_motor_on) ? false : true;
                    }
                    if (_motor_on || _motor_reverse) {
                        if (_motor_reverse) {
                            motor.front().move(MAX_VOLTS*MOTOR_SENSITIVITY * -1);
                        } else {
                            motor.front().move(MAX_VOLTS*MOTOR_SENSITIVITY);
                        }
                    } else {
                        motor.front().brake();
                    }
                } else if (_press_type == kt::ON_PRESS && _reverse_press_type == kt::ON_NEW_PRESS) {
                    // on press and on new press
                    if (master.get_digital(_keybind)) {
                        _motor_reverse = true;
                    } else {
                        _motor_reverse = false;
                    }
                    if (master.get_digital_new_press(_reverse_keybind)) {
                        _motor_on = (_motor_on) ? false : true;
                    }
                    if (_motor_on || _motor_reverse) {
                        if (_motor_reverse) {
                            motor.front().move(MAX_VOLTS*MOTOR_SENSITIVITY * -1);
                        } else {
                            motor.front().move(MAX_VOLTS*MOTOR_SENSITIVITY);
                        }
                    } else {
                        motor.front().brake();
                    }
                } else {
                    // both are on press
                    if (master.get_digital(_keybind)) {
                        motor.front().move(MAX_VOLTS*MOTOR_SENSITIVITY);
                    } else if (master.get_digital(_reverse_keybind)) {
                        motor.front().move(MAX_VOLTS*MOTOR_SENSITIVITY * -1);
                    } else {
                        motor.front().brake();
                    }
                }
                //_motor_on = (_motor_on) ? false : true;
                //motor.front().move(MAX_VOLTS*MOTOR_SENSITIVITY * -1);
                //motor.front().move(MAX_VOLTS*MOTOR_SENSITIVITY);
                //motor.front().brake();
            } else {
                // no reverse data motor opc
                if (_press_type == kt::ON_NEW_PRESS) {
                    // on new press
                    if (master.get_digital_new_press(_keybind)) {
                        _motor_on = (_motor_on) ? false : true;
                    }
                } else {
                    // on press
                    if (master.get_digital(_keybind)) {
                        _motor_on = true;
                    } else {
                        _motor_on = false;
                    }
                }
                if (_motor_on) {
                        motor.front().move(MAX_VOLTS*MOTOR_SENSITIVITY);
                } else {
                        motor.front().brake();
                }
            }
        }
    }
};