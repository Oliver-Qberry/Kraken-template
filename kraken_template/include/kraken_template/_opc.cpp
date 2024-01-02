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
                    // has data for stock opc
                    // motor data
                    // _keybind
                    // _in_toggle_mode
                    // _have_reverse_keybind
                    // _reverse_keybind

                    // has_pid_kval
                    // kpid
                    // _target_velocity
                    // _cartrage_rpm

                    
                }
            }
        }
    }

    void _adi() {
        // adi out
        if (devices.ADIDigitalOut.added_adi) {
            for (const auto& name : devices.ADIDigitalOut.get_ADI_names()) {
                if (devices.ADIDigitalOut.get_ADI_node(name).has_adv_data) {
                    // has data for stock opc
                    // adi data
                    // _keybind
                    // _in_toggle_mode
                    // _reverse_flow

                    bool active = (devices.ADIDigitalOut.get_ADI_node(name)._reverse_flow) ? true : false;
                    bool inactive = (devices.ADIDigitalOut.get_ADI_node(name)._reverse_flow) ? false : true;

                    if (devices.ADIDigitalOut.get_ADI_node(name)._in_toggle_mode) {
                        // in toggle mode
                        if (devices.controller.master().get_digital_new_press(devices.ADIDigitalOut.get_ADI_node(name)._keybind)) {
                            devices.ADIDigitalOut.get_ADI_node(name).toggle_current_toggle();
                        }
                        if (devices.ADIDigitalOut.get_ADI_node(name)._current_toggle) {
                            devices.ADIDigitalOut.get_ADI_node(name).get_adiout().set_value(active);
                        } else {
                            devices.ADIDigitalOut.get_ADI_node(name).get_adiout().set_value(inactive);
                        }
                    } else {
                        // not in toggle mode
                        if (devices.controller.master().get_digital(devices.ADIDigitalOut.get_ADI_node(name)._keybind)) {
                            devices.ADIDigitalOut.get_ADI_node(name).get_adiout().set_value(active);
                        } else {
                            devices.ADIDigitalOut.get_ADI_node(name).get_adiout().set_value(inactive);
                        }
                    }
                }
            }
        }
    }
};

OPC opc;