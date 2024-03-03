#pragma once

#include "kt/devices/motor/motor_node.hpp"
#include "pros/motors.hpp"

#include <string>
#include <unordered_map>

namespace kt {
// class to handle motors
class Motor {
    private:
    // motor node map
    std::unordered_map<std::string, motor_node> node_map;

    public:
    // add a new motor to the handler (no complex info)
    /*
    parameters:
        name.
        port.
    */
    void new_motor(std::string name, int port);

    // add a new motor to the handler (with data for opc, no rev)
    /*
    parameters:
        name.
        port.
        keybind.
        press type.
    */
    void new_motor(std::string name, int port, 
                   pros::controller_digital_e_t keybind, kt::e_press_type press_type);

    // add a new motor to the handler (with data for opc, with rev)
    /*
    parameter:
        name.
        port.
        keybind.
        press type
        reverse keybind
        reverse press type
    */
    void new_motor(std::string name, int port, 
               pros::controller_digital_e_t keybind, kt::e_press_type press_type, 
               pros::controller_digital_e_t reverse_keybind, kt::e_press_type reverse_press_type);

    // add a new PID motor to the handler (with data for opc, pid)
    /*
    parameter:
        name.
        port.
        motor gearset.
        target velocity.
        vector<int> pid constants
        pid exit range
    */
    void new_motor(std::string name, int port, pros::controller_digital_e_t keybind, e_press_type press_type, pros::v5::MotorGears motor_gearset, 
                   double target_velocity, 
                   std::vector<double> pid_k_constants, double range = 0);

    // gets motor by its name
    pros::Motor get_motor(std::string name);

    // sets a motors brake mode by its name
    void set_brake_mode(std::string name, pros::motor_brake_mode_e_t brake);

    // runs the opcontrol function for a motor by its name
    void opcontrol(std::string name);

    // gets node and motor data by its name
    motor_node get_motor_data(std::string name);

    // pid on / off by name
    void pid(std::string name, bool pid_on);

    // set a motors pid target velocity
    void pid_set_target_velocity(std::string name, double target_velocity);

    // sets a motors P I D constants
    void pid_set_k_constants(std::string name, std::vector<double> pid_k_constants);

    // sets a motors exit range
    void pid_set_range(std::string name, double range);

    // checks if a motors pid goal is met. returns a bool
    bool pid_is_goal_met(std::string name);

}; // end of Motor class
} // end of kt namespace