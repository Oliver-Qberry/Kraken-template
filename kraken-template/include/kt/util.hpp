#pragma once

#include "api.h"



extern pros::Controller master;

namespace kt {

enum e_lcd_button {
    LCD_LEFT_BUTTON = 0,
    LCD_RIGHT_BUTTON = 1,
    LCD_MIDDLE_BUTTON = 2
};

enum e_press_type {
    ON_PRESS = 0,
    ON_NEW_PRESS = 1
};

enum e_bool{
    LOOK_FOR_FALSE = false,
    LOOK_FOR_TRUE = true
};
/*
used to set if a device should be in toggle mode
*/
enum e_toggle_mode {
    IN_TOGGLE_MODE = true,
    NOT_TOGGLE_MODE = false
};




namespace util {

// returns the sign of the input.
int sgn(double input);
/* 
checks the sign of the input and returns false is the input is positive and true if the input is netative.
this is used to check if a motor needs to be revered from the passed ports sign.
*/
bool reversed_active(double input);
/*
returns the number of degrees between 2 angles in degrees. works over 0 and is directional.
*/
double imu_error_calc(double current, double target);



const int DELAY_TIME = 20;

}
}