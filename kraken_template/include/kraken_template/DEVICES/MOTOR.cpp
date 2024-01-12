#pragma once
#include "main.h"

#include "nodes/MOTOR_Node.cpp"

#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

class _MOTOR {
    private:
        std::vector<std::string> node_names;
        std::unordered_map<std::string, Node_MOTOR> node_map;

    public:
        bool added_motor = false;

        void new_motor(std::string name, int port, pros::motor_brake_mode_e_t brake_mode, bool reverse = false) {
            this->node_names.push_back(name);
            node_map[name] = Node_MOTOR(name, port, brake_mode, reverse);
            this->added_motor = true;
        }

        void set_motor_keybinds(std::string name, 
                                pros::controller_digital_e_t keybind, 
                                bool in_toggle_mode = false, int voltage = 127, bool have_reverse_keybind = false, 
                                pros::controller_digital_e_t reverse_keybind = pros::E_CONTROLLER_DIGITAL_X) {
            this->node_map[name].set_data(keybind, in_toggle_mode, voltage, have_reverse_keybind, reverse_keybind);
        }

        void set_pid_values(std::string name, double kp, double ki, double kd) {
            this->node_map[name].set_pid_kval(kp, ki, kd);
        }

        void set_pid_target_velocity(std::string name, double target_velocity, double range, double cartrage_rpm) {
            this->node_map[name].set_pid_target(target_velocity, range, cartrage_rpm);
        }

        pros::Motor get_motor(std::string name) {
            return node_map[name].get_motor();
        }

        bool pid_within_goal(std::string name) {
            if (node_map[name].pid().goal_met()) {
                return true;
            }
            return false;
        }

        std::vector<std::string> get_motor_names() {
            return node_names;
        }

        Node_MOTOR get_motor_node(std::string name) {
            return this->node_map[name];
        }
};