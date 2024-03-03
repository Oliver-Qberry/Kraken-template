#include "kt/devices/motor/motor_node.hpp"
#include "kt/util.hpp"

void motor_node::opcontrol() {
    // if motor has enough data for opc
    if (_has_data_for_opc) { 


        // PID


        // if motor has data for pid
        if (_has_data_for_pid) {
            // pid on new press
            if (_press_type == kt::ON_NEW_PRESS) {
                if (master.get_digital_new_press(_keybind)) {
                    _pid_on = (_pid_on) ? false : true;
                }
            // pid on press
            } else {
                if (master.get_digital(_keybind)) {
                    this->_pid_on = true;
                } else {
                    this->_pid_on = false;
                }
            } // end of pid keybind
            // get current pid out
            this->pid_volts_out = motor_pid_controller.calculate(motor.front().get_actual_velocity());
            // check or swap pid out
            if (pid_volts_out*MOTOR_SENSITIVITY > MAX_VOLTS) {
                pid_volts_out = MAX_VOLTS;
            }
            // if pid is active
            if (_pid_on == true) {
                // motor volts set to pid out
                motor.front().move(pid_volts_out*MOTOR_SENSITIVITY);
            // else pid is inactive
            } else {
                motor.front().brake();
            }


        // reverse data


        // if motor has reverse data
        } else if (_has_reverse_data) {
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


        // no reverse data


        } else {
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


        } // end of motor data type
    } // end of motor has data for opc
} // end of opcontrol function