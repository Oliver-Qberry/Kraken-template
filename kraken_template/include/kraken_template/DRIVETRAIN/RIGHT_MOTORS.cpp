#pragma once
#include "main.h"
#include <vector>

class _RIGHT_MOTORS {
    private:
        std::vector<pros::Motor> right_motors_vector;
    public:
        _RIGHT_MOTORS() {} // empty constructor
        _RIGHT_MOTORS(std::vector<pros::Motor> right_motors_vector) {
            this->right_motors_vector = right_motors_vector;

        }


        void move(int voltage) {}
        
};