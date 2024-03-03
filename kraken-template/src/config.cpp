// kt includes
#include "config.hpp"
#include "kt/devices/motor/motor.hpp"
#include "kt/util.hpp"
#include "pros/misc.h"

// namespace
using namespace pros;
using namespace kt;
using namespace v5;

// ==================== setup your devices functions here ==================== //
/*
this is were you can setup your robots devices. this function will be called during initialize() in main.cpp
and any changes to the kt device classes will be kept and can then be used in both main.cpp and auton.cpp.
the exception to this is the chassis which is defined in main.cpp.
*/
void initialize_devices() {
    // define your devices here using their subclasses for them to be brought to both auton and main files


    // initialize the brains lcd for the auton select
    lcd::initialize();


    // an example of how to setup a motor
    motor.new_motor("motor", 1, E_CONTROLLER_DIGITAL_B, ON_PRESS);


} // end of initialize_devices function

// ==================== setup your devices functions here ==================== //
/*
this function is used to print data to the brain. it will run after initialize when the robot is turned on.
writing to the brain is done with the pros::lcd object.

feel free to add or remove anything from this function but remember that the while loop is needed for it to update
and the pros::delay helps it run better.
*/
void print_to_lcd_task() {
    while (true) {
        // print branding
        lcd::set_text(0, "Kraken Template");
        // print the current auton name
        lcd::set_text(1, autons.current_name());
        // print the current auton description
        lcd::set_text(2, autons.current_desc());
        // print the current drive imu heading
        lcd::set_text(3, std::to_string(chassis.imu.get_heading()));
        

        // you can always remove some of these or add more


        // make sure to have some delay
        pros::delay(kt::util::DELAY_TIME);
    } // end of main loop
} // end of print_to_lcd_task function