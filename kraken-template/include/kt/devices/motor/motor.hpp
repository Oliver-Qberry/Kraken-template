#pragma once

#include "kt/devices/motor/motor_node.hpp"
#include "pros/motors.hpp"
#include <string>
#include <unordered_map>


namespace kt {
class Motor {
    private:
    std::unordered_map<std::string, motor_node> node_map;
    public:

    void new_motor(std::string name, int port) {
        pros::Motor new_mot(port);
        node_map[name].motor.clear();
        node_map[name].motor.push_back(new_mot);
    }

    void new_motor(std::string name, int port, 
                   pros::controller_digital_e_t keybind, kt::e_press_type press_type) {
        pros::Motor new_mot(port);
        node_map[name].motor.clear();
        node_map[name].motor.push_back(new_mot);
        node_map[name]._keybind = keybind;
        node_map[name]._press_type = press_type;
        node_map[name]._has_data_for_opc = true;
    }

    void new_motor(std::string name, int port, 
               pros::controller_digital_e_t keybind, kt::e_press_type press_type, 
               pros::controller_digital_e_t reverse_keybind, kt::e_press_type reverse_press_type) {
        pros::Motor new_mot(port);
        node_map[name].motor.clear();
        node_map[name].motor.push_back(new_mot);
        node_map[name]._keybind = keybind;
        node_map[name]._press_type = press_type;
        node_map[name]._reverse_keybind = reverse_keybind;
        node_map[name]._reverse_press_type = reverse_press_type;
        node_map[name]._has_data_for_opc = true;
        node_map[name]._has_reverse_data = true;
    }

    void new_motor(std::string name, int port, pros::v5::MotorGears motor_gearset, 
                   double target_velocity, 
                   std::vector<double> pid_k_constants, double range = 0) {
        pros::Motor new_mot(port, motor_gearset);
        node_map[name].motor.clear();
        node_map[name].motor.push_back(new_mot);
        node_map[name].motor_pid_controller.set_pid_constants(pid_k_constants[0], pid_k_constants[1], pid_k_constants[2]);
        node_map[name].motor_pid_controller.set_goal(target_velocity, range);
        node_map[name].motor_pid_controller.reset();
        node_map[name]._has_data_for_opc = true;
        node_map[name]._has_data_for_pid = true;
    }

    pros::Motor get_motor(std::string name) {
        return node_map[name].motor.front();
    }

    void set_brake_mode(std::string name, pros::motor_brake_mode_e_t brake) {
        node_map[name].motor.front().set_brake_mode(brake);
    }

    void opcontrol(std::string name) {
        node_map[name].opcontrol();
    }

    motor_node get_motor_data(std::string name) {
        return node_map[name];
    }

    void pid(std::string name, bool pid_on) {
        // flip _pid_on to pid_on
        node_map[name]._pid_on = pid_on;
    }

    void pid_set_target_velocity(std::string name, double target_velocity) {
        node_map[name].motor_pid_controller.set_goal(target_velocity);
    }

    void pid_set_k_constants(std::string name, std::vector<double> pid_k_constants) {
        node_map[name].motor_pid_controller.set_pid_constants(
            pid_k_constants[0],pid_k_constants[1],pid_k_constants[2]);
    }

    void pid_set_range(std::string name, double range) {
        node_map[name].motor_pid_controller.set_range(range);
    }

    bool pid_is_goal_met(std::string name) {
        return node_map[name].motor_pid_controller.goal_met();
    }
};
}