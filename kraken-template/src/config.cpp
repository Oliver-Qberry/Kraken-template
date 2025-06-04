// kt includes
#include "config.hpp"
#include "kt/devices/motor/motor.hpp"
#include "kt/util.hpp"
// other includes
#include "pros/misc.h"
#include "main.h"

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
void initialize_devices()
{
    // define your devices here using their subclasses for them to be brought to both auton and main files

    // initialize the brains lcd for the auton select
    lcd::initialize();

    // an example of how to setup a motor
    motor.new_motor("motor", 1, E_CONTROLLER_DIGITAL_B, ON_PRESS);

} // end of initialize_devices function

// ==================== setup your devices functions here ==================== //
std::string display_odometry_position()
{
    if (chassis.get_odometry_status())
    {
        return "(" + std::to_string(chassis.x) + ", " + std::to_string(chassis.y) + ") Angle: " + std::to_string(chassis.theta);
    }
    else
    {
        return "Odometry not enabled";
    }
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
        // master.set_text(3, 0, "lcd task");

        // lcd::set_text(4, display_odometry_position());

        /*if (chassis.error != "")
        {
            lcd::set_text(7, "Error: " + chassis.error);
        }
        else
        {
            lcd::set_text(7, "No errors");
        }*/

        // you can always remove some of these or add more

        // make sure to have some delay
        pros::delay(kt::util::DELAY_TIME);
    } // end of main loop
} // end of print_to_lcd_task function

void print_to_controller_task()
{
    while (true)
    {
        if (!autons.is_editing())
        {
            // normal display
        }
        else
        {
            master.clear();
            // editing display
            master.set_text(0, 0, "add command");
            master.set_text(1, 0, "run");
        }
        pros::delay(50);
    }
}

// TODO: have it be more dynamic in the array location to work with 3 sensors
// TODO: add arc support
// FIXME: MATH IS WRONG, output is way to small

void update_position_task()
{
    while (std::isnan(chassis.imu.get_heading()) || std::isinf(chassis.imu.get_heading()))
    {
    }

    while (chassis.get_odometry_status())
    {
        // Get current sensor readings
        double current_forward_reading = chassis.odom_rotation_sensors[0].get_position();
        double current_rotation_reading = chassis.odom_rotation_sensors[1].get_position();

        // Calculate sensor deltas
        double delta_forward = current_forward_reading - chassis.prev_forward_sensor;
        double delta_rotation = current_rotation_reading - chassis.prev_rotation_sensor;

        // Update previous sensor readings
        chassis.prev_forward_sensor = current_forward_reading;
        chassis.prev_rotation_sensor = current_rotation_reading;

        // Rotation from sensor
        double rotation_distance = (delta_rotation / 36000.0) * (M_PI * chassis.odom_wheel_diameter);
        double rotation_angle_change = (rotation_distance / chassis.horizontal_tracking_center) * (180.0 / M_PI);

        // Rotation from IMU
        double current_imu_angle = chassis.imu.get_heading(); // Already in degrees
        double imu_angle_change = kt::util::imu_error_calc(chassis.prev_imu_angle, current_imu_angle);
        chassis.prev_imu_angle = current_imu_angle;

        // Average rotation change
        double delta_angle = (rotation_angle_change + imu_angle_change) / 2.0;

        // Distance traveled
        double delta_distance = (delta_forward / 36000.0) * (M_PI * chassis.odom_wheel_diameter);

        // Arc-based position update
        double delta_x, delta_y;

        if (fabs(delta_angle) < 1e-6)
        {
            // Straight line
            double theta_rad = chassis.theta * (M_PI / 180.0);
            delta_x = delta_distance * cos(theta_rad);
            delta_y = delta_distance * sin(theta_rad);
        }
        else
        {
            // Arc motion
            double theta_rad = chassis.theta * (M_PI / 180.0);
            double delta_angle_rad = delta_angle * (M_PI / 180.0);
            double radius = delta_distance / delta_angle_rad;

            delta_x = radius * (sin(theta_rad + delta_angle_rad) - sin(theta_rad));
            delta_y = radius * (-cos(theta_rad + delta_angle_rad) + cos(theta_rad));
        }

        // Update position and heading
        chassis.x += delta_x;
        chassis.y += delta_y;
        chassis.theta += delta_angle;

        pros::delay(kt::util::DELAY_TIME);
    }
}

// temp

// Alternative method with better accuracy for larger movements:
/*void update_odometry_arc()
{
    // Get current sensor readings
    double current_forward = chassis.odom_rotation_sensors[0].get_position();
    double current_rotation = chassis.odom_rotation_sensors[1].get_position();

    // Calculate sensor deltas
    double delta_forward = current_forward - chassis.prev_forward_sensor;
    double delta_rotation = current_rotation - chassis.prev_rotation_sensor;

    // Update previous readings
    chassis.prev_forward_sensor = current_forward;
    chassis.prev_rotation_sensor = current_rotation;

    // Calculate angle change
    double rotation_distance = (delta_rotation / 36000.0) * (M_PI * chassis.odom_wheel_diameter);
    double rotation_angle_change = (rotation_distance / chassis.horizontal_tracking_center) * (180.0 / M_PI);

    double current_imu_angle = chassis.imu.get_heading(); // Already in degrees
    double imu_angle_change = current_imu_angle - chassis.prev_imu_angle;
    chassis.prev_imu_angle = current_imu_angle;

    // Handle wraparound
    if (imu_angle_change > 180.0)
        imu_angle_change -= 360.0;
    else if (imu_angle_change < -180.0)
        imu_angle_change += 360.0;

    double delta_angle = (rotation_angle_change + imu_angle_change) / 2.0;

    // Calculate forward distance
    double delta_distance = (delta_forward / 36000.0) * (M_PI * chassis.odom_wheel_diameter);

    // Arc-based calculation for better accuracy
    double delta_x, delta_y;

    if (fabs(delta_angle) < 1e-6)
    {
        // Straight line movement - convert theta to radians for trig
        double theta_rad = chassis.theta * (M_PI / 180.0);
        delta_x = delta_distance * cos(theta_rad);
        delta_y = delta_distance * sin(theta_rad);
    }
    else
    {
        // Arc movement - convert angles to radians for calculations
        double theta_rad = chassis.theta * (M_PI / 180.0);
        double delta_angle_rad = delta_angle * (M_PI / 180.0);
        double radius = delta_distance / delta_angle_rad;
        delta_x = radius * (sin(theta_rad + delta_angle_rad) - sin(theta_rad));
        delta_y = radius * (-cos(theta_rad + delta_angle_rad) + cos(theta_rad));
    }

    // Update position and angle

    chassis.x += delta_x;
    chassis.y += delta_y;
    chassis.theta += delta_angle;

    pros::delay(kt::util::DELAY_TIME);
}*/

void auton_editor_task()
{
    enum class Level
    {
        Overview,
        AddCommand,
        EditCommandParams
    };
    Level current_location = Level::Overview;
    int selectorLine = 0; // 0-2
    bool rightyLatch = false;
    int threashold = 50;

    autons.set_editing(true);
    while (true)
    {
        if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_R1))
        {
            // tab forward
        }
        else if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_L1))
        {
            // tab back
        }
        else if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_A))
        {
            // accept/enter
        }
        else if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_B))
        {
            // Back to last level
        }
        else if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_UP))
        {
            // next option/increment
        }
        else if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_DOWN))
        {
            // last option/deincrement
        }
        else if (master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y) > threashold && !rightyLatch)
        {
            rightyLatch = true;
            //"scroll" up
        }
        else if (master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y) < (-1 * threashold) && !rightyLatch)
        {
            rightyLatch = true;
            // scroll down
        }
        else
        {
            rightyLatch = false;
        }

        pros::delay(kt::util::DELAY_TIME);
    }
}