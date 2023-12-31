#pragma once
#include "main.h"

#include "LEFT_MOTORS.cpp"
#include "RIGHT_MOTORS.cpp"
#include "DRIVE_IMU.cpp"

#include <vector>

class _DRIVETRAIN {
    private:
        std::vector<pros::Motor> left_motors_vector;
        std::vector<pros::Motor> right_motors_vector;
        std::vector<pros::Imu> imu;

        double gearset_rpm_ratio;

    public:
        _LEFT_MOTORS left_motors;
        _RIGHT_MOTORS right_motors;

        bool added_drivetrain_motors = false;
        bool added_drivetrain_imu = false;

        void set_motor_ports(std::vector<int> left_ports, std::vector<int> right_ports, 
                             pros::motor_brake_mode_e_t brake_type, bool reversed = false) {
            this->left_motors_vector.clear();
            this->right_motors_vector.clear();

            bool lrb = false; // left right reverse control
            bool rrb = true;
            if (reversed) {
                lrb = true;
                rrb = false;
            }

            // populate the motor vectors
            // left motors
            for (const auto& element : left_ports) {
                pros::Motor new_motor(element, lrb);
                new_motor.set_brake_mode(brake_type);
                this->left_motors_vector.push_back(new_motor);
            }
            this->left_motors = _LEFT_MOTORS(left_motors_vector); // populate subclass
            // right motors
            for (const auto& element : right_ports) {
                pros::Motor new_motor(element, rrb); // right motors are reversed
                new_motor.set_brake_mode(brake_type);
                this->right_motors_vector.push_back(new_motor);
            }
            this->right_motors = _RIGHT_MOTORS(right_motors_vector);
            this->added_drivetrain_motors = true;
        }

        void set_rpm(int motor_rpm, double wheel_rpm, double wheel_diameter) {

            this->gearset_rpm_ratio = 0; /////////////////// DO THIS MATH
        }

        void set_imu_port(int _port) {}



        void set_drive_pid() {}
        void set_turn_pid() {}

        void move(double distance) {}

        void move(double distance, double angle) {}

        void turn(double angle) {}



        





};