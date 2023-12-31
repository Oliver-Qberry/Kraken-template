#pragma once
#include "main.h"
#include <vector>

class _LEFT_MOTORS {
    private:
        std::vector<pros::Motor> left_motors_vector;
    public:
        _LEFT_MOTORS() {} // empty constructor
        _LEFT_MOTORS(std::vector<pros::Motor> left_motors_vector) {
            this->left_motors_vector = left_motors_vector;

        }


        void move(int voltage) {}
        
};