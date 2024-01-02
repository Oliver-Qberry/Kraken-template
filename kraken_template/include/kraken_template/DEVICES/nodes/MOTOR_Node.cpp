#pragma once
#include "main.h"

#include "kraken_template/pid/pid.cpp"

class Node_MOTOR {
    private:
        PIDController motor_pid;
    public:
        std::string _name;
        std::vector<pros::Motor> motor;

        bool has_adv_data = false;
        pros::controller_digital_e_t _keybind;
        bool _in_toggle_mode;
        int _voltage;
        bool _have_reverse_keybind;
        pros::controller_digital_e_t _reverse_keybind;

        bool _current_toggle = false;
        int _dir = 1;

        bool has_pid_kval = false;
        bool has_pid_target = false;
        double kpid[3];
        double _target_velocity;
        double _range;
        double _cartrage_rpm;




        Node_MOTOR (std::string _name, int _port, pros::motor_brake_mode_e_t _brake_mode, bool _reverse = false) {
            this->_name = _name;
            pros::Motor new_motor(_port, _reverse);
            new_motor.set_brake_mode(_brake_mode);
            this->motor.clear();
            this->motor.push_back(new_motor);
        }

        void set_data(pros::controller_digital_e_t _keybind, bool _in_toggle_mode, int _voltage, 
                      bool _have_reverse_keybind, pros::controller_digital_e_t _reverse_keybind) {
            this->_keybind = _keybind;
            this->_in_toggle_mode = _in_toggle_mode;
            this->_voltage = _voltage;
            this->_have_reverse_keybind = _have_reverse_keybind;
            this->_reverse_keybind = _reverse_keybind;
            this->has_adv_data = true;
        }

        void set_pid_kval(double _kp, double _ki, double _kd) {
            this->kpid[0] = _kp;
            this->kpid[1] = _ki;
            this->kpid[2] = _kd;
            this->motor_pid = PIDController(_kp, _ki, _kd);
            this->has_pid_kval = true;
        }

        void set_pid_target(double _target_velocity, double _range, double _cartrage_rpm) {
            this->_target_velocity = _target_velocity;
            this->_cartrage_rpm = _cartrage_rpm;
            this->_range = _range;
            this->has_pid_target = true;
        }

        void toggle_current_toggle() {
            this->_current_toggle = (this->_current_toggle) ? false : true;
        }

        void set_dir(int direction) {
            this->_dir = direction;
        }

        PIDController pid() {return this->motor_pid;}

        pros::Motor get_motor() {return motor.front();}
};