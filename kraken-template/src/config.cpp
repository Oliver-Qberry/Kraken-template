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

        lcd::set_text(4, display_odometry_position());

        // you can always remove some of these or add more

        // make sure to have some delay
        pros::delay(kt::util::DELAY_TIME);
    } // end of main loop
} // end of print_to_lcd_task function

void update_position_task()
{
    while (chassis.get_odometry_status())
    {
        // FIXME: are the calculations right
        //  Get the angle
        double rotation_angle = (chassis.odom_rotation_sensors[1].get_position() / 100);
        // divide by 100.0
        double angle = (rotation_angle * chassis.odom_wheel_diameter) / chassis.horizontal_tracking_center;
        double imu_angle = chassis.imu.get_heading();
        angle = (angle + imu_angle) / 2;
        double delta_angle = angle - chassis.theta;
        chassis.prev_theta = chassis.theta;
        chassis.theta += delta_angle /*fmod(delta_angle, 360)*/;

        /*double delta_angle = fmod(angle + 180.0, 360.0);
        if (delta_angle < 0)
            delta_angle += 360.0; // Ensure positive result from fmod
        delta_angle -= 180.0;     // an average heading
        */

        // get the cordinate position
        double rotation = chassis.odom_rotation_sensors[0].get_position();
        double delta_distance_y = ((rotation / 36000) * (M_PI * chassis.odom_wheel_diameter) * sin(chassis.theta)) - chassis.y; // delta from last position
        chassis.prev_y = chassis.y;
        chassis.y += delta_distance_y;

        double delta_distance_x = ((rotation / 36000) * (M_PI * chassis.odom_wheel_diameter) * cos(chassis.theta)) - chassis.x; // delta from last position
        chassis.prev_x = chassis.x;
        chassis.x += delta_distance_x;

        pros::delay(kt::util::DELAY_TIME);
    }
}

// TODO: have it be more dynamic in the array location to work with 3 sensors
// TODO: add arc support
void update_position_task_2()
{
    // FIXME: MATH IS WRONG, output is way to small
    while (std::isnan(chassis.imu.get_heading()) || std::isinf(chassis.imu.get_heading()))
    {
    }
    while (chassis.get_odometry_status())
    {
        // get current sensor readings
        double current_forward_reading = chassis.odom_rotation_sensors[0].get_position();
        double current_rotation_reading = chassis.odom_rotation_sensors[1].get_position();
        // Calculate sensor deltas (change since last reading)
        double delta_forward = current_forward_reading - chassis.prev_forward_sensor;
        double delta_rotation = current_rotation_reading - chassis.prev_rotation_sensor;

        // Update previous sensor readings for next iteration
        chassis.prev_forward_sensor = current_forward_reading;
        chassis.prev_rotation_sensor = current_rotation_reading;

        // Calculate angle change from rotation sensor
        // Convert sensor ticks to distance, then to angle in degrees
        double rotation_distance = (delta_rotation / 36000.0) * ((M_PI * chassis.odom_wheel_diameter));
        double rotation_angle_change = (rotation_distance / chassis.horizontal_tracking_center) * (180.0 / M_PI);

        // Get IMU angle change
        double current_imu_angle = chassis.imu.get_heading(); // Already in degrees
        double imu_angle_change = current_imu_angle - chassis.prev_imu_angle;
        chassis.prev_imu_angle = current_imu_angle;
        // Handle IMU angle wraparound (if using 0-360 degrees)
        if (imu_angle_change > 180.0)
        {
            imu_angle_change -= 360.0;
        }
        else if (imu_angle_change < -180.0)
        {
            imu_angle_change += 360.0;
        }

        // Average the two angle measurements for better accuracy
        double average_delta_angle = (rotation_angle_change + imu_angle_change) / 2.0; // this is nan and some times imu_angle_change, until imu gets a vlaue
        // Update robot's heading
        // TODO: is this check still needed.
        if (!std::isnan(average_delta_angle))
        {
            chassis.theta += average_delta_angle;
        }
        else
        {
            chassis.theta += 0;
        }
        // theta is inf until imu starts outputing values and then is nan

        // Calculate forward distance traveled
        double delta_distance = (delta_forward / 36000.0) * (M_PI * chassis.odom_wheel_diameter);

        // Calculate position changes using the average angle during this movement
        // Use theta + delta_angle/2 for more accuracy (midpoint approximation)
        double avg_angle = (chassis.theta - average_delta_angle) / 2.0;

        // Convert angle to radians for trig functions
        double avg_angle_rad = avg_angle * (M_PI / 180.0);
        double delta_x = delta_distance * cos(avg_angle_rad);
        double delta_y = delta_distance * sin(avg_angle_rad);

        // Update position
        chassis.x += delta_x;
        chassis.y += delta_y;

        pros::delay(kt::util::DELAY_TIME);
    }
}

// temp

// Alternative method with better accuracy for larger movements:
void update_odometry_arc()
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
}