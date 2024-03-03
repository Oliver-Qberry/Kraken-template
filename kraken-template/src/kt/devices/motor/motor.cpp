#include "kt/devices/motor/motor.hpp"
#include "kt/util.hpp"
#include "pros/misc.h"

void kt::Motor::new_motor(std::string name, int port) {
    pros::Motor new_mot(port);
    node_map[name].motor.clear();
    node_map[name].motor.push_back(new_mot);
}

void kt::Motor::new_motor(std::string name, int port, 
               pros::controller_digital_e_t keybind, kt::e_press_type press_type) {
    pros::Motor new_mot(port);
    node_map[name].motor.clear();
    node_map[name].motor.push_back(new_mot);
    node_map[name]._keybind = keybind;
    node_map[name]._press_type = press_type;
    node_map[name]._has_data_for_opc = true;
}

void kt::Motor::new_motor(std::string name, int port, 
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

void kt::Motor::new_motor(std::string name, int port, 
                          pros::controller_digital_e_t keybind, e_press_type press_type, 
                          pros::v5::MotorGears motor_gearset, double target_velocity, 
                          std::vector<double> pid_k_constants, double range) {
    pros::Motor new_mot(port, motor_gearset);
    node_map[name].motor.clear();
    node_map[name].motor.push_back(new_mot);
    node_map[name].motor_pid_controller.set_pid_constants(pid_k_constants[0], pid_k_constants[1], pid_k_constants[2]);
    node_map[name].motor_pid_controller.set_goal(target_velocity, range);
    node_map[name].motor_pid_controller.reset();
    node_map[name]._has_data_for_opc = true;
    node_map[name]._has_data_for_pid = true;
    node_map[name]._keybind = keybind;
    node_map[name]._press_type = press_type;
}

pros::Motor kt::Motor::get_motor(std::string name) {
    return node_map[name].motor.front();
}

void kt::Motor::set_brake_mode(std::string name, pros::motor_brake_mode_e_t brake) {
    node_map[name].motor.front().set_brake_mode(brake);
}

void kt::Motor::opcontrol(std::string name) {
    node_map[name].opcontrol();
}

motor_node kt::Motor::get_motor_data(std::string name) {
    return node_map[name];
}

void kt::Motor::pid(std::string name, bool pid_on) {
    // flip _pid_on to pid_on
    node_map[name]._pid_on = pid_on;
}

void kt::Motor::pid_set_target_velocity(std::string name, double target_velocity) {
    node_map[name].motor_pid_controller.set_goal(target_velocity);
}

void kt::Motor::pid_set_k_constants(std::string name, std::vector<double> pid_k_constants) {
    node_map[name].motor_pid_controller.set_pid_constants(
            pid_k_constants[0],pid_k_constants[1],pid_k_constants[2]);
}

void kt::Motor::pid_set_range(std::string name, double range) {
    node_map[name].motor_pid_controller.set_range(range);
}

bool kt::Motor::pid_is_goal_met(std::string name) {
    return node_map[name].motor_pid_controller.goal_met();
}