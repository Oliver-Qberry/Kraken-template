#pragma once
#include "main.h"

class Node_MOTOR {
    public:
        std::string _name;
        std::vector<pros::Motor> motor;

        bool has_adv_data = false;
        pros::controller_digital_e_t _keybind;
        bool _in_toggle_mode;
        bool _have_reverse_keybind;
        pros::controller_digital_e_t _reverse_keybind;

        bool has_pid_kval = false;
        double kpid[3];
        double _target_velocity;
        double _cartrage_rpm;


        Node_MOTOR (std::string _name, int _port, pros::motor_brake_mode_e_t _brake_mode, bool _reverse = false) {
            this->_name = _name;
            pros::Motor new_motor(_port, _reverse);
            new_motor.set_brake_mode(_brake_mode);
            this->motor.clear();
            this->motor.push_back(new_motor);
        }

        void set_data(pros::controller_digital_e_t _keybind, bool _in_toggle_mode, bool _have_reverse_keybind, 
                      pros::controller_digital_e_t _reverse_keybind) {
            this->_keybind = _keybind;
            this->_in_toggle_mode = _in_toggle_mode;
            this->_have_reverse_keybind = _have_reverse_keybind;
            this->_reverse_keybind = _reverse_keybind;
            this->has_adv_data = true;
        }

        void set_pid_kval(double _kp, double _ki, double _kd) {
            this->kpid[0] = _kp;
            this->kpid[1] = _ki;
            this->kpid[2] = _kd;
            this->has_pid_kval = true;
        }

        void set_pid_target(double _target_velocity, double _cartrage_rpm) {
            this->_target_velocity = _target_velocity;
            this->_cartrage_rpm = _cartrage_rpm;
        }

        pros::Motor get_motor() {return motor.front();}
};