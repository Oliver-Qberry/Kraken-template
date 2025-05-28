#pragma once

#include "api.h"
#include "kt/util.hpp"
#include "kt/pid.hpp"

namespace kt
{
    // class that combines drive motors, drive imu, and drive pid. Used to move the robot.
    class Chassis
    {
    private:
        // if in tank drive mode
        bool _tank_drive = false;
        bool odometry = false;

    public:
        // x controller analog channel id
        pros::controller_analog_e_t controller_x_id;
        // y controller analog channel id
        pros::controller_analog_e_t controller_y_id;
        // x threshold
        int JOYSTICK_X_THRESHOLD = 0;
        // y threshold
        int JOYSTICK_Y_THRESHOLD = 0;
        // x sensitivity
        double JOYSTICK_X_SENSITIVITY = 1;
        // y sensitivity
        double JOYSTICK_Y_SENSITIVITY = 1;
        // saved max voltage
        double max_volts = 127;
        // left motor vector
        std::vector<pros::Motor> left_motors;
        // right motor vector
        std::vector<pros::Motor> right_motors;
        // integrated imu object
        pros::Imu imu;
        // saved motor rpm
        double motor_rpm;
        // saved wheel rpm
        double wheel_rpm;
        // saved wheel diameter
        double wheel_diameter;
        // odometry
        double odom_wheel_diameter;
        double horizontal_tracking_center;
        double vertical_tracking_center;
        std::vector<pros::Rotation> odom_rotation_sensors;
        // odometry based position
        double x = 0, y = 0, theta = 0;
        double prev_forward_sensor, prev_rotation_sensor, prev_imu_angle;
        double prev_x, prev_y, prev_theta;

        // pid objects
        kt::util::PIDController drive_pid_controller;
        // pid objects
        kt::util::PIDController turn_pid_controller;
        // resets the integrated encoders and imu heading.
        void initialize();
        /*
        constructor parameters:
            vector<int>, left motor ports
            vector<int>, right motor ports
            motor_brake_mode_e_t, drive brake type
            int, drive imu port
            double, motor cartrage rpm
            double, drive wheels rpm
            double, drive wheel diameter
        */
        Chassis(std::vector<int> left_motor_ports, std::vector<int> right_motor_ports,
                pros::motor_brake_mode_e_t brake_type, int imu_port,
                double motor_rpm, double wheel_rpm, double wheel_diameter);
        // tank drive opc
        void opcontrol_tank();
        // single stick drive opc
        void opcontrol_arcade_standard();
        // single stick opc flipped
        void opcontrol_arcade_flipped();
        // double stick opc
        void opcontrol_split_standard();
        // double stick opc flipped
        void opcontrol_split_flipped();
        // enable odometry
        void enable_odometry(std::vector<int> sensor_ports, double wheel_diameter, double h_tracking_center, double v_tracking_center);
        bool get_odometry_status();
        // integrated. set drive pid constants and exit range
        void drive_pid_constants(double drive_kP, double drive_kI, double drive_kD, double drive_range);
        // integrated. set turn pid constants and exit range
        void turn_pid_constants(double turn_kP, double turn_kI, double turn_kD, double turn_range);
        /*
        complex move function. parameters:
            double, distance to move forward (negative for reverse)
            double, angle to turn (0 to not turn at all)
            double, turn multiplier = 1 (how much the turn error is taken into account. set to 0 for 1d pid)
        */
        void move(double distance, double angle, double turn_multi = 1);
        // move function. pass a voltage (-127 to 127)
        void move(int voltage);
        void move_to(double x, double y, int theta);
        // turn function. pass a voltage (-127 to 127)
        void turn(int voltage);
        // brake the drive motors
        void brake();
        // set the drive motor brake modes
        void set_brake_modes(pros::motor_brake_mode_e_t brake);
        // runs integrated opc function
        void opcontrol();
        // resets the motors encoder values
        void reset_integrated_encoders();
        // resets the rotation sensors values
        void reset_odometry_sensors();
        // gets the average motor encoder values
        double get_average_integrated_encoders_positions();

    }; // end of chassis class
} // end of kt namespace