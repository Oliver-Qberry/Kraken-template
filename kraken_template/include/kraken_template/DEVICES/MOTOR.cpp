#pragma once
#include "main.h"
#include <string>
#include <tuple>
#include <unordered_map>

class _MOTOR {
    private:
        std::vector<std::string> motor_names;
        std::vector<pros::Motor> motor_motors;

        std::unordered_map<std::string, bool> map_motor_has_data;
        std::unordered_map<std::string, pros::controller_digital_e_t> map_motor_data_keybind;
        std::unordered_map<std::string, bool> map_motor_data_in_toggle_mode;
        std::unordered_map<std::string, bool> map_motor_data_have_reverse_keybind;
        std::unordered_map<std::string, pros::controller_digital_e_t> map_motor_data_reverse_keybind;

        std::unordered_map<std::string, bool> map_motor_data_have_pid;
        std::unordered_map<std::string, std::tuple<double, double, double>> map_motor_pid_kval;

    public:
        bool added_motor = false;

        void _new(std::string name, int port_, pros::motor_brake_mode_e_t brake_mode, bool reverse_ = false) {
            this->added_motor = true;
            pros::Motor new_motor(port_, reverse_);
            new_motor.set_brake_mode(brake_mode);

            this->motor_names.push_back(name);
            this->motor_motors.push_back(new_motor);

            this->map_motor_data_have_pid[name] = false;
        }

        void set_motor_keybinds(std::string name, 
                                pros::controller_digital_e_t keybind, 
                                bool in_toggle_mode, bool have_reverse_keybind = false, 
                                pros::controller_digital_e_t reverse_keybind = pros::E_CONTROLLER_DIGITAL_X) {

            this->map_motor_data_keybind[name] = keybind;
            this->map_motor_data_in_toggle_mode[name] = in_toggle_mode;
            this->map_motor_data_have_reverse_keybind[name] = have_reverse_keybind;
            this->map_motor_data_reverse_keybind[name] = reverse_keybind;
        }

        void set_motor_pid(std::string name, double kp, double ki, double kd) {
            this->map_motor_data_have_pid[name] = true;
            std::tuple<double, double, double> ktup = {kp, ki, kd};
            this->map_motor_pid_kval[name] = ktup;
            }

        std::vector<std::string> get_motor_data_motor_names() {return this->motor_names;}

        bool get_motor_has_data(std::string name) {
            return this->map_motor_has_data[name];}

        pros::controller_digital_e_t get_motor_data_keybind(std::string name) {
            return this->map_motor_data_keybind[name];}

        bool get_motor_data_in_toggle_mode(std::string name) {
            return this->map_motor_data_in_toggle_mode[name];}

        bool get_motor_data_have_reverse_keybind(std::string name) {
            return this->map_motor_data_have_reverse_keybind[name];}

        pros::controller_digital_e_t get_motor_data_reverse_keybind(std::string name) {
            return this->map_motor_data_reverse_keybind[name];}

        bool get_motor_data_have_pid(std::string name) {
            return this->map_motor_data_have_pid[name];}

        pros::Motor motor(std::string name) {
            if (this->added_motor) {
                auto it = std::find(this->motor_names.begin(), this->motor_names.end(), name);
                if (it != this->motor_names.end()) {
                    auto idx = std::distance(this->motor_names.begin(), it);
                    return this->motor_motors[idx];
                }
            }
            pros::Motor n(0);
            return n;
        }
};