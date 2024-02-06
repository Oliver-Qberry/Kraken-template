/*

*/
// includes the pros and kt api
#include "main.h"
// includes the config file for device setup
#include "config.hpp"
// includes the auton file for auton setup
#include "auton.hpp"
#include <string>
/*

*/
using namespace std;
using namespace pros;
/*

*/
kt::Chassis chassis(

    {11, 12, 13}, 

    {-14, -15, -16}, 

    E_MOTOR_BRAKE_COAST, 

    17, 

    600,

    450,

    3.25
    );
/*
*/
kt::AUTONS autons(
    // keybind for auto select
    pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_DOWN);
/*
*/
kt::ADI_DIGITALIN AdiDigitalIn;
kt::ADI_DIGITALOUT AdiDigitalOut;
kt::Distance distance;
kt::IMU imu;
kt::Motor motor;
kt::Rotation rotation;


void initialize() {
    // device init
    lcd::initialize();
    lcd::set_text(0, "2605A");
    initialize_devices();

    // chassis init
    chassis.opcontrol_split_standard();
    chassis.initialize();

    // sets up auton class
    initialize_auton();
    // starts the auto select task
    Task task_auton(initialize_task);

}

void competition_initialize() {}

void autonomous() {autons.run_current_auton();}


void opcontrol() {
    chassis.CURRENT_BRAKE = E_MOTOR_BRAKE_COAST;
    while (true) {

        motor.opcontrol("intake");
        chassis.opcontrol();

        AdiDigitalOut.opcontrol("test");



        pros::delay(kt::util::DELAY_TIME);
    }
}

void disabled() {}