#pragma once
#include "main.h"

/*
ktv class and its sub classes are used to store pros variables needed to setup the robot.
this way they are easier to get as you dont have to remember as much.
*/

class PVC {
    private:
        class CONSTRAINTS {
            public:
                bool above = true;
                bool below = false;
                bool if_true = true;
                bool if_false = false;
                
        };
        class CONTROLLER {
            public:
                pros::controller_analog_e_t left_stick_x = pros::E_CONTROLLER_ANALOG_LEFT_X;
                pros::controller_analog_e_t left_stick_y = pros::E_CONTROLLER_ANALOG_LEFT_Y;
                pros::controller_analog_e_t right_stick_x = pros::E_CONTROLLER_ANALOG_RIGHT_X;
                pros::controller_analog_e_t right_stick_y = pros::E_CONTROLLER_ANALOG_RIGHT_Y;

                pros::controller_digital_e_t A =  pros::E_CONTROLLER_DIGITAL_A;
                pros::controller_digital_e_t B = pros::E_CONTROLLER_DIGITAL_B;
                pros::controller_digital_e_t X = pros::E_CONTROLLER_DIGITAL_X;
                pros::controller_digital_e_t Y = pros::E_CONTROLLER_DIGITAL_Y;

                pros::controller_digital_e_t UP =pros::E_CONTROLLER_DIGITAL_UP;
                pros::controller_digital_e_t DOWN = pros::E_CONTROLLER_DIGITAL_DOWN;
                pros::controller_digital_e_t LEFT = pros::E_CONTROLLER_DIGITAL_LEFT;
                pros::controller_digital_e_t RIGHT = pros::E_CONTROLLER_DIGITAL_RIGHT;

                pros::controller_digital_e_t L1 = pros::E_CONTROLLER_DIGITAL_L1;
                pros::controller_digital_e_t L2 = pros::E_CONTROLLER_DIGITAL_L2;

                pros::controller_digital_e_t R1 = pros::E_CONTROLLER_DIGITAL_R1;
                pros::controller_digital_e_t R2 = pros::E_CONTROLLER_DIGITAL_R2;
        };
        class BRAKE {
            public:
                pros::motor_brake_mode_e_t coast = pros::E_MOTOR_BRAKE_COAST;
                pros::motor_brake_mode_e_t brake = pros::E_MOTOR_BRAKE_BRAKE;
                pros::motor_brake_mode_e_t hold = pros::E_MOTOR_BRAKE_HOLD;
                pros::motor_brake_mode_e_t invalid = pros::E_MOTOR_BRAKE_INVALID;
        };


    public:
        CONTROLLER controller;
        BRAKE brake;
        CONSTRAINTS constraints;
};