/*




    Checklist guide to making your robot move with the kraken template
        1. setup the chassis class in this file
            go to the kt::Chassis chassis definition follow the instructions

            go to the initialize function and follow the instructions there to setup the chassis controls

            go to the operator control (opcontrol) function and make sure chassis.opcontrol() is called

        2. populate the devices classes

        3. add some autons (not required)


*/
// includes the pros and kt api
#include "main.h"
// includes the config file for device setup
#include "config.hpp"
// includes the auton file for auton setup
#include "auton.hpp"
/*
using the std and pros namespace.
kt namespace is still being used as there is crossover between kt and pros.
*/
using namespace std;
using namespace pros;
/*

*/
kt::Chassis chassis(
    // the first 2 parameters of the chassis class definition are integer vectors of the motors ports on the brain.
    // note that a negative integer will make the motor be reversed
    // first pass a int vector of the left motor ports
    {11, 12, 13}, 
    // second pass a int vector of the right motor ports
    {-14, -15, -16}, 
    // pass a brake type
    // found in pors::E_MOTOR_BRAKE_(type) or just uncomment one of the below
    E_MOTOR_BRAKE_COAST, 
    //E_MOTOR_BRAKE_BRAKE,
    //E_MOTOR_BRAKE_HOLD,

    // the imu port which is used to calculate the robots heading
    17, 
    // the rpm of the motor
    // remember that red = 100, green = 200, blue = 600
    600,
    // next is the wheel rpm
    // if the gear ratio between the motor and wheel is 1:1 its the same as the motor_rpm otherwise multiply
    // the motor_rpm by the gear ratio to get the wheel_rpm
    450,
    // last is the diameter of the wheel in inches
    // remember that 4" wheels are actually 4.125
    3.25
    );
/*
*/
kt::AUTONS autons(
    // keybind for auto select
    E_CONTROLLER_DIGITAL_DOWN);
/*
*/
kt::ADI_DIGITALIN AdiDigitalIn;
kt::ADI_DIGITALOUT AdiDigitalOut;
kt::Distance distance;
kt::IMU imu;
kt::Motor motor;
kt::Rotation rotation;

/*
*/
void initialize() {

    /*
    */
    chassis.opcontrol_split_standard();
	//chassis.opcontrol_split_flipped();
	//chassis.opcontrol_arcade_standard();
	//chassis.opcontrol_arcade_flipped();
	//chassis.opcontrol_tank();

    // chassis init
    chassis.initialize();

    // device init
    initialize_devices();

    // sets up auton class
    initialize_auton();

    // starts the auto select task
    Task task_auton(auton_select_task);
	// starts lcd print task
	Task task_lcd(print_to_lcd_task);

}

/*
*/
void competition_initialize() {}
void disabled() {}

/*

*/
void opcontrol() {
    while (true) {





		chassis.opcontrol();

        delay(kt::util::DELAY_TIME);
    }
}

/*
*/
void autonomous() {autons.run_current_auton();}