#pragma once
#include "main.h"
#include <vector>

class _DRIVE_MOTORS {
    private:
        std::vector<pros::Motor> motors_vector;
    public:
        _DRIVE_MOTORS() {} // empty constructor
        _DRIVE_MOTORS(std::vector<pros::Motor> motors_vector) {
            this->motors_vector = motors_vector;

        }


        void move(int voltage) {
            for (const auto& motor : motors_vector) {
                motor.move(voltage);
            }
        }

        double get_pos() {
            int num_of_motors = 0;
            double total_pos_of_motor = 0;

            for (const auto& motor : motors_vector) {
                num_of_motors++;
                total_pos_of_motor += motor.get_position();
            }
            return total_pos_of_motor/num_of_motors;
        }
        
        void set_pos(double new_position) {
            for (const auto& motor : motors_vector) {
                motor.set_zero_position(0);
            }
        }
};