/*
Kraken Template by Cole Johnson of 2605E
In collaboration with Oliver Quessenberry of 2605A

template is made for SHS VRC teams and is based off of what we have at SHS and need for the VRC robot
*/
// includes the pros and kt api
#include "main.h"
// includes the devices file for device setup
#include "devices.hpp"

#include "kt/util.hpp"
// includes the auton file for auton setup
#include "auton.hpp"
// other includes here
#include "pros/misc.h"

/*
a few different namespaces are adding for your convenience.
HOWEVER remember that there is some crossover between kt and pros so you may still have to use them in some cases.
*/
using namespace std;
using namespace pros;
using namespace v5;
using namespace kt;

namespace kt::devices
{
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

    kt::ADI_DIGITALIN AdiDigitalIn;
    kt::ADI_DIGITALOUT AdiDigitalOut;
    kt::Distance distance;
    kt::IMU imu;
    kt::Motor motor;
    kt::Rotation rotation;

    void initialize_devices()
    {
        lcd::initialize();

        motor.new_motor("motor", 1);

        rotation.new_rotation("rotation sensor", 2);
    }

    /*
    this function is used to print data to the brain. it will run after initialize when the robot is turned on.
    writing to the brain is done with the pros::lcd object.

    feel free to add or remove anything from this function but remember that the while loop is needed for it to update
    and the pros::delay helps it run better.
    */
    void print_to_lcd_task()
    {
        while (true)
        {
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

    void print_to_controller_task()
    {
        while (true)
        {
            master.set_text(0, 0, "Hello");

            pros::delay(50);
        }
    }

    void chassis_setup()
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

        // ========== Set default PID constants ==========
        // FIXME: users can override these later in their device setup
        chassis.drive_pid_constants(.5, .000000001, .00001, 10);
        chassis.turn_pid_constants(.5, .000000001, .00001, 10);
    }

} // namespace kt::devices