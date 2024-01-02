#include "main.h"
#include "_config.cpp"


class OPC {
    public:

    void _drivetrain() {
        if (drivetrain.added_drivetrain_motors && devices.controller.get_data_drive_keybinds_set()) {
            // get current controller data
            int c_master_anaX = devices.controller.master().get_analog(devices.controller.get_ana_x()); 
            int c_master_anaY = devices.controller.master().get_analog(devices.controller.get_ana_y());

            // check and set sens
            double x_sens = 1, y_sens = 1;
            if (devices.controller.get_data_drive_sens_set()) {
                x_sens = devices.controller.get_x_sensitivity();
                y_sens = devices.controller.get_y_sensitivity();
            }

            // check and set reverse
            int rev = 1;
            if (devices.controller.get_data_reverse_drive_direction()) {
                rev = -1;
            }

            // move motors at mapped voltages
            drivetrain.left_motors.move((c_master_anaY*y_sens*-c_master_anaX*x_sens));
            drivetrain.right_motors.move((c_master_anaY*y_sens+c_master_anaX*x_sens));
        }
    }

    void _motor() {
        // motor
        if (devices.motor.added_motor) {
            for (const auto& name : devices.motor.get_motor_names()) {
                if (devices.motor.get_motor_node(name).has_adv_data) {
                    Node_MOTOR node = devices.motor.get_motor_node(name);
                    // has data for stock opc
                    // motor data
                    // _keybind
                    // _in_toggle_mode
                    // _voltage
                    // _have_reverse_keybind
                    // _reverse_keybind

                    // has_pid_kval
                    // kpid
                    // _target_velocity
                    // _cartrage_rpm

                    if (node.has_pid_kval && node.has_pid_target) {
                        // pid controller
                        node.pid().set_goal(node._target_velocity, node._range);
                        double out = node.pid().calculate(average_drive_positions(drivetrain.left_motors, drivetrain.right_motors));
                        if (out > node._voltage) {
                            out = node._voltage;
                        } // let voltage act as a max voltage
                        if (node._in_toggle_mode) {
                            // pid in toggle mode
                            if (devices.controller.master().get_digital_new_press(node._keybind)) {
                                if (node._dir != -1) {
                                    node.toggle_current_toggle();
                                }
                                node.set_dir(1);
                            } else if (devices.controller.master().get_digital_new_press(node._reverse_keybind)) {
                                if (node._dir != 1) {
                                    node.toggle_current_toggle();
                                }
                                node.set_dir(-1);
                            }
                            if (node._current_toggle) {
                                node.get_motor().move(out * node._dir);
                            } else {
                                node.get_motor().brake();
                            }
                        } else {
                            // pid not in toggle mode
                            if (devices.controller.master().get_digital(node._keybind)) {
                                node.get_motor().move(out);
                            } else {
                                node.get_motor().brake();
                            }
                        }
                    } else {
                        // motor does not have pid setup
                        if (node._in_toggle_mode) {
                            // motor in toggle mode
                            if (node._have_reverse_keybind) {
                                // reverse keybind mode
                                if (devices.controller.master().get_digital_new_press(node._keybind)) {
                                    if (node._dir != -1) {
                                        node.toggle_current_toggle();
                                    }
                                    node.set_dir(1);
                                } else if (devices.controller.master().get_digital_new_press(node._reverse_keybind)) {
                                    if (node._dir != 1) {
                                        node.toggle_current_toggle();
                                    }
                                    node.set_dir(-1);
                                }
                                if (node._current_toggle) {
                                    node.get_motor().move(node._voltage * node._dir);
                                } else {
                                    node.get_motor().brake();
                                }
                            } else {
                                // no reverse keybind
                                if (devices.controller.master().get_digital_new_press(node._keybind)) {
                                    node.toggle_current_toggle();
                                }
                                if (node._current_toggle) {
                                    node.get_motor().move(node._voltage);
                                } else {
                                    node.get_motor().brake();
                                }
                            }
                        } else {
                            //motor not in toggle mode
                            if (node._have_reverse_keybind) {
                                // reverse keybind mode
                                if (devices.controller.master().get_digital(node._keybind)) {
                                    node.get_motor().move(node._voltage);
                                } else if (devices.controller.master().get_digital(node._reverse_keybind)) {
                                    node.get_motor().move(node._voltage*-1);
                                } else {
                                    node.get_motor().brake();
                                }
                            } else {
                                // no reverse keybind
                                if (devices.controller.master().get_digital(node._keybind)) {
                                    node.get_motor().move(node._voltage);
                                } else {
                                    node.get_motor().brake();
                                }
                            }
                        }
                    }                    
                }
            }
        }
    }

    void _adi() {
        // adi out
        if (devices.ADIDigitalOut.added_adi) {
            for (const auto& name : devices.ADIDigitalOut.get_ADI_names()) {
                if (devices.ADIDigitalOut.get_ADI_node(name).has_adv_data) {
                    Node_ADIDigitalOut node = devices.ADIDigitalOut.get_ADI_node(name);
                    // has data for stock opc
                    // adi data
                    // _keybind
                    // _in_toggle_mode
                    // _reverse_flow

                    bool active = (node._reverse_flow) ? true : false;
                    bool inactive = (node._reverse_flow) ? false : true;

                    if (node._in_toggle_mode) {
                        // in toggle mode
                        if (devices.controller.master().get_digital_new_press(node._keybind)) {
                            node.toggle_current_toggle();
                        }
                        if (node._current_toggle) {
                            node.get_adiout().set_value(active);
                        } else {
                            node.get_adiout().set_value(inactive);
                        }
                    } else {
                        // not in toggle mode
                        if (devices.controller.master().get_digital(node._keybind)) {
                            node.get_adiout().set_value(active);
                        } else {
                            node.get_adiout().set_value(inactive);
                        }
                    }
                }
            }
        }
    }
};

OPC opc;