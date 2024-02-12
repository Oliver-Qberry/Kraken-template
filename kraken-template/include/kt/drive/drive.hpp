#pragma once

#include "api.h"

#include "kt/util.hpp"
#include "kt/pid.hpp"





namespace kt {

    class Chassis {
        private:
            bool _tank_drive = false;
        public:

            pros::controller_analog_e_t controller_x_id;
            pros::controller_analog_e_t controller_y_id;

            int JOYSTICK_X_THRESHOLD = 0;
            int JOYSTICK_Y_THRESHOLD = 0;

            double JOYSTICK_X_SENSITIVITY = 1;
            double JOYSTICK_Y_SENSITIVITY = 1;

            //pros::motor_brake_mode_e_t CURRENT_BRAKE = pros::E_MOTOR_BRAKE_COAST;

            double max_volts = 127;

            std::vector<pros::Motor> left_motors;

            std::vector<pros::Motor> right_motors;

            pros::Imu imu;

            double motor_rpm;
            double wheel_rpm;
            double wheel_diameter;

            // pid objects
            kt::util::PIDController drive_pid_controller;
            kt::util::PIDController turn_pid_controller;

            void initialize();  

            Chassis(std::vector<int> left_motor_ports, std::vector<int> right_motor_ports,
                    pros::motor_brake_mode_e_t brake_type, int imu_port, double motor_rpm, double wheel_rpm, double wheel_diameter);

            void opcontrol_tank();

            void opcontrol_arcade_standard();

            void opcontrol_arcade_flipped();

            void opcontrol_split_standard();

            void opcontrol_split_flipped();

            void drive_pid_constants(double drive_kP, double drive_kI, double drive_kD, double drive_range);
            
            void turn_pid_constants(double turn_kP, double turn_kI, double turn_kD, double turn_range);

            void move(double distance, double angle, double turn_multi = 1);

            void move(int voltage);

            void turn(int voltage);

            void brake();

            void set_brake_modes(pros::motor_brake_mode_e_t brake);

            void opcontrol();

            void reset_integrated_encoders();

            double get_average_integrated_encoders_positions();
    };
}