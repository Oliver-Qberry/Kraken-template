/*
Kraken Template by Cole Johnson of 2605E
In collaboration with 2605A

template is made for SHS VRC teams and is based off of what we have at SHS and need for the VRC robot
*/
// includes the pros and kt api
#include "main.h"
// includes the config file for device setup
#include "config.hpp"
// includes the auton file for auton setup
#include "auton.hpp"
// other includes here

/*
a few different namespaces are adding for your convenience.
HOWEVER remember that there is some crossover between kt and pros so you may still have to use them in some cases.
*/
using namespace std;
using namespace pros;
using namespace v5;
using namespace kt;

// ==================== chassis setup ==================== //
/*
this is the main chassis definition. this class is what you will be using to setup your robots chassis / drivetrain
and will help your move your robot.
follow the steps below to setup the class.
*/
kt::Chassis chassis(
    // the first 2 parameters of the chassis class definition are integer vectors of the motors ports on the brain.
    // note that a negative integer will make the motor be reversed
    // first pass a int vector of the left motor ports
    {-10, -9, -8},
    // second pass a int vector of the right motor ports
    {16, 15, 14},

    // pass a brake type
    // found in pros::E_MOTOR_BRAKE_(type) or just uncomment one of the below (we recommend coast)
    E_MOTOR_BRAKE_COAST,
    // E_MOTOR_BRAKE_BRAKE,
    // E_MOTOR_BRAKE_HOLD,

    // the imu port which is used to calculate the robot's heading
    7, // 18

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

); // end of chassis class setup

// ==================== auton selector setup ==================== //
/*
this is the main autons class definition. it is used to handle all the autons you make and has build in auton
select on the controller.
right now you can only use a controller to select what auton you want to use but that might change in the future.
*/
kt::AUTONS autons(
    // pass a controller keybind for auto select
    E_CONTROLLER_DIGITAL_DOWN

); // end of autons class setup

/*
these are the device class definitions. they store information about the devices on your robot and allow you
to access that information in this file, as well as in config.cpp and autons.cpp.

DO NOT CHANGE THESE

setting up devices should be done in the initialize_devices() in the config.cpp file.

AGAIN DO NOT CHANGE THESE
*/
kt::ADI_DIGITALIN AdiDigitalIn;
kt::ADI_DIGITALOUT AdiDigitalOut;
kt::Distance distance;
kt::IMU imu;
kt::Motor motor;
kt::Rotation rotation;

// ==================== initialize ==================== //
/*
the initialize function is run when the program is started.

all other competition modes are blocked by initialize so it is recommended
to keep execution time for this mode under a few seconds.
*/
void initialize()
{
    /*
    this is were you can change the control scheme for your drivetrain during opcontrol.
    simply uncomment one of the lines below.
    */
    chassis.opcontrol_split_standard();
    // chassis.opcontrol_split_flipped();
    // chassis.opcontrol_arcade_standard();
    // chassis.opcontrol_arcade_flipped();
    // chassis.opcontrol_tank();

    // enable the use of odometry, uncomment to use odometry
    chassis.enable_odometry(
        // the ports for the rotation sensors, first one is vertical(forward/backward), second is horizontal
        // negative is if its reveresed
        {9, -8},
        // tracking wheel diameter, mostlikly 2 inch
        2.0,
        // the distance in inches from the tracking center to the front/back wheel
        3.0,
        // the distance in inches from the tracking center to the left/right wheel
        1.0);

    // ========== other initialize functions ========== //
    // chassis initialize -> chassis
    chassis.initialize();
    // device initialize -> config.cpp
    initialize_devices();
    // auton initialize -> auton.cpp
    initialize_auton();

    // ========== task functions ========== //
    Task task_odometry(update_position_task_2);
    // starts the auto select task
    Task task_auton(auton_select_task);
    // starts lcd print task
    Task task_lcd(print_to_lcd_task);

    // put anything else you want to add below here

    // Default PID vlaues
    // FIXME: tune these
    chassis.drive_pid_constants(.5, .000000001, .00001, 10);
    chassis.turn_pid_constants(.5, .000000001, .00001, 10);

} // end of initialize function

// ==================== competition initialize ==================== //
/*
runs after initialize(), and before autonomous when connected to the field
management system or the vex competition switch.

this task will exit when the robot is enabled and autonomous or opcontrol starts.

this is not used in the base kraken template but feel free to add to it.
*/
void competition_initialize() {}

// ==================== disabled ==================== //
/*
runs while the robot is in the disabled state of field management system or
the vex competition switch, following either autonomous or opcontrol. when
the robot is enabled, this task will exit.

this is not used in the base kraken template but feel free to add to it.
*/
void disabled() {}

// ==================== operator control ==================== //
/*
runs the operator control code. this function will be started whenever the robot is enabled via
the field management system or the vex competition switch in the operator control mode.

if no competition control is connected, this function will run immediately following initialize().

if the robot is disabled or communications is lost, the operator control task will be stopped.
re-enabling the robot will restart the task, not resume it from where it left off.
*/
void opcontrol()
{
    // the while loop constantly loops the function while the task is active
    while (true)
    {
        // TODO: auton writing while in driver control

        // your operator control code should go here

        // this is an example of how you can use the motors build in opcontrol function
        // this is the same motor setup in initialize_devices in config.cpp
        motor.opcontrol("motor");

        // this is how you can call the build in opcontrol function for the chassis class
        chassis.opcontrol();

        // a small delay is needed to prevent issues
        delay(kt::util::DELAY_TIME);
    } // end of while loop
} // end of opcontrol function

// ==================== autonomous ==================== //
/*
runs the user autonomous code. This function will be started whenever the robot is enabled via
the field management system or the vex competition switch in the autonomous mode.

if the robot is disabled or communications is lost, the autonomous task
will be stopped. re-enabling the robot will restart the task, not re-start it
from where it left off.

with the kraken template and autons class, it will run whatever the current auton is during autonomous.
the current auton can be changed by using the auton selector.
*/
void autonomous() { autons.run_current_auton(); }