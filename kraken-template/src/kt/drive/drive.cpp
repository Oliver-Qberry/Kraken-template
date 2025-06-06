#include "kt/drive/drive.hpp"
#include "kt/pid.hpp"
#include "kt/util.hpp"
#include "liblvgl/llemu.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include <string>

void kt::Chassis::initialize()
{
    // resets imu and encoders
    imu.reset();
    reset_integrated_encoders();
    if (odometry)
    {
        reset_odometry_sensors();
    }
} // end of init function

kt::Chassis::Chassis(std::vector<int> left_motor_ports, std::vector<int> right_motor_ports,
                     pros::motor_brake_mode_e_t brake_type,
                     int imu_port,
                     double motor_rpm, double wheel_rpm, double wheel_diameter) : imu(imu_port),
                                                                                  motor_rpm(motor_rpm), wheel_rpm(wheel_rpm), wheel_diameter(wheel_diameter)
{
    // populate left motor vector
    for (auto i : left_motor_ports)
    {
        pros::Motor motor(abs(i));
        motor.set_reversed(kt::util::reversed_active(i));
        motor.set_brake_mode(brake_type);
        left_motors.push_back(motor);
    }
    // populate right motor vector
    for (auto i : right_motor_ports)
    {
        pros::Motor motor(abs(i));
        motor.set_reversed(kt::util::reversed_active(i));
        motor.set_brake_mode(brake_type);
        right_motors.push_back(motor);
    }
} // end of chassis constructor

void kt::Chassis::enable_odometry(std::vector<int> sensor_ports, double wheel_diameter, double h_tracking_center, double v_tracking_center)
{
    odometry = true;
    odom_wheel_diameter = wheel_diameter;
    horizontal_tracking_center = h_tracking_center;
    vertical_tracking_center = v_tracking_center;
    for (auto i : sensor_ports)
    {
        pros::Rotation rotation(abs(i));
        if (i < 0)
        {
            rotation.set_reversed(true);
        }
        odom_rotation_sensors.push_back(rotation);
    }
    prev_forward_sensor = 0;
    prev_imu_angle = 0;
    prev_rotation_sensor = 0;
    prev_theta = 0;
    prev_x = 0;
    prev_y = 0;
}

void kt::Chassis::opcontrol_tank()
{
    // set the analog channel ids for tank control
    _tank_drive = true;
    controller_x_id = pros::E_CONTROLLER_ANALOG_LEFT_Y;
    controller_y_id = pros::E_CONTROLLER_ANALOG_RIGHT_Y;
}

void kt::Chassis::opcontrol_arcade_standard()
{
    // set the analog channel ids for arcade control
    _tank_drive = false;
    controller_x_id = pros::E_CONTROLLER_ANALOG_LEFT_X;
    controller_y_id = pros::E_CONTROLLER_ANALOG_LEFT_Y;
}

void kt::Chassis::opcontrol_arcade_flipped()
{
    // set the analog channel ids for arcade flipped control
    _tank_drive = false;
    controller_x_id = pros::E_CONTROLLER_ANALOG_RIGHT_X;
    controller_y_id = pros::E_CONTROLLER_ANALOG_RIGHT_Y;
}

void kt::Chassis::opcontrol_split_standard()
{
    // set the analog channel ids for split control
    _tank_drive = false;
    controller_x_id = pros::E_CONTROLLER_ANALOG_RIGHT_X;
    controller_y_id = pros::E_CONTROLLER_ANALOG_LEFT_Y;
}

void kt::Chassis::opcontrol_split_flipped()
{
    // set the analog channel ids for split flipped control
    _tank_drive = false;
    controller_x_id = pros::E_CONTROLLER_ANALOG_LEFT_X;
    controller_y_id = pros::E_CONTROLLER_ANALOG_RIGHT_Y;
}

void kt::Chassis::reset_odometry_sensors()
{
    for (auto &rotation : odom_rotation_sensors)
    {
        rotation.reset_position();
    }
}
bool kt::Chassis::get_odometry_status()
{
    return odometry;
}

void kt::Chassis::reset_integrated_encoders()
{
    // reset left motors
    for (auto motor : left_motors)
    {
        motor.set_zero_position(0);
    }
    // reset right motors
    for (auto motor : right_motors)
    {
        motor.set_zero_position(0);
    }
}

double kt::Chassis::get_average_integrated_encoders_positions()
{
    // sum of left
    double left_sum = 0;
    for (auto motor : left_motors)
    {
        left_sum += motor.get_position();
    }
    // avg of left motors
    double left_avg = left_sum / left_motors.size();
    // sum of right
    double right_sum = 0;
    for (auto motor : right_motors)
    {
        right_sum += motor.get_position();
    }
    // avg of right motors
    double right_avg = right_sum / right_motors.size();
    // return avg of the 2
    return (left_avg + right_avg) / 2;
}

void kt::Chassis::brake()
{
    // brake left motors
    for (auto motor : left_motors)
    {
        motor.brake();
    }
    // brake right motors
    for (auto motor : right_motors)
    {
        motor.brake();
    }
}

void kt::Chassis::set_brake_modes(pros::motor_brake_mode_e_t brake)
{
    // set brake for left motors
    for (auto motor : left_motors)
    {
        motor.set_brake_mode(brake);
    }
    // set brake for right motors
    for (auto motor : right_motors)
    {
        motor.set_brake_mode(brake);
    }
}

/*TODO: problems
- drifting
- turn exiting loop
- turn power is to much, using .5 multiplier
- add a slight delay after finishing a command/ at the end of this function .3-.6 seconds
- filter the derivative
*/

void kt::Chassis::move(double distance, double angle, double turn_multi)
{
    // reset drive motor encoders
    reset_integrated_encoders();
    // get the gearset ratio of the motor encoder
    double gearset_rpm_ratio = ((50.0) / ((motor_rpm) / (3600.0))) * ((motor_rpm) / (wheel_rpm));
    // get the actual distance needed to travel in ticks
    // double distanceIn = (((gearset_rpm_ratio * distance) / wheel_diameter)) / 2;
    double distanceIn = (distance / (wheel_diameter * 3.14)) * (wheel_rpm / motor_rpm) * (180000 / motor_rpm);
    // setup drive pid controller
    drive_pid_controller.reset();
    drive_pid_controller.set_goal(distanceIn);
    double current_pos, drive_output;
    // get the target angle
    imu.set_heading(0);
    double target_angle = imu.get_heading() + angle;
    // setup turn pid controller
    turn_pid_controller.reset();
    turn_pid_controller.set_goal(angle); // target_angle
    double turn_error, turn_output;
    // if turn multi is 0 bypass the pid so goalmet will always be true
    if (turn_multi == 0)
    {
        turn_pid_controller.bypass = true;
    }
    else
    {
        turn_pid_controller.bypass = false;
    } // end of bypass if else
    // create direction integer variables
    int left_dir, right_dir;

    // pid loop
    do
    {
        // find the current position with the motor encoders
        current_pos = get_average_integrated_encoders_positions();
        // get the drive pid output
        drive_output = drive_pid_controller.calculate(current_pos);
        // get the current turn error (target - current)
        turn_error = kt::util::imu_error_calc(imu.get_heading(), angle); // target angle
        // get the turn pid output
        turn_output = turn_pid_controller.calculate_turn(turn_error);
        // check the direction of the turn output to set signs

        left_dir = (kt::util::sgn(turn_error));
        right_dir = (kt::util::sgn(turn_error)) * -1;
        // if it drifts off cource we want it to correct
        // set moves voltage to outputs
        for (auto motor : left_motors)
        {
            motor.move(drive_output + (/*turn_error*/ turn_output * left_dir * turn_multi));
        }
        // should one of these subtract, maybe not becuase direction is + or -
        for (auto motor : right_motors)
        {
            motor.move(drive_output + (/*turn_error*/ turn_output * right_dir * turn_multi));
        }
        // delay
        pros::delay(kt::util::DELAY_TIME);
    } while ((!drive_pid_controller.goal_met() && distance != 0) || (!turn_pid_controller.goal_met()) /* && angle != 0*/);
    brake();

    // TODO: delay by a small amount? jsut for smoother transition between commands
} // end of move complex function

void kt::Chassis::move_to(std::initializer_list<kt::purePursuit::Point> path, double finalAngle)
{
    drive_pid_controller.reset();
    // set goal
    // kt::purePursuit::Point goal = path.back();//get goal (last point)
}

void kt::Chassis::move_to(kt::purePursuit::Point destination, double endAngle)
{
    move(0, asin(abs(y - destination.y)), 1.0);
    // reset drive motor encoders
    double distance = sqrt(pow(x - destination.x, 2) + pow(y - destination.y, 2));
    // get the gearset ratio of the motor encoder
    double gearset_rpm_ratio = ((50.0) / ((motor_rpm) / (3600.0))) * ((motor_rpm) / (wheel_rpm));
    // get the actual distance needed to travel in ticks
    // double distanceIn = (((gearset_rpm_ratio * distance) / wheel_diameter)) / 2;
    double centidegrees = distance / (odom_wheel_diameter * M_PI) * 36000;
    // setup drive pid controller
    drive_pid_controller.reset();
    drive_pid_controller.set_goal(centidegrees + odom_rotation_sensors[0].get_position());
    double current_pos, drive_output;
    // get the target angle
    double target_angle = imu.get_heading() + asin(abs(y - destination.y));
    // setup turn pid controller
    turn_pid_controller.reset();
    turn_pid_controller.set_goal(target_angle); // target_angle
    double turn_error, turn_output;
    // if turn multi is 0 bypass the pid so goalmet will always be true
    /*if (turn_multi == 0)
    {
        turn_pid_controller.bypass = true;
    }
    else
    {
        turn_pid_controller.bypass = false;
    }*/
    // end of bypass if else
    // create direction integer variables
    int left_dir, right_dir;
    // pid loop
    do
    {
        // find the current position with the motor encoders
        current_pos = odom_rotation_sensors[0].get_position(); // what do we set as the current position.
        // get the drive pid output
        drive_output = drive_pid_controller.calculate(current_pos);
        // get the current turn error (target - current)
        turn_error = kt::util::imu_error_calc(imu.get_heading(), target_angle); // target angle
        // get the turn pid output
        turn_output = turn_pid_controller.calculate_turn(turn_error);
        // check the direction of the turn output to set signs

        left_dir = (kt::util::sgn(turn_error));
        right_dir = (kt::util::sgn(turn_error)) * -1;
        // if it drifts off cource we want it to correct
        // set moves voltage to outputs
        for (auto motor : left_motors)
        {
            motor.move(drive_output + (/*turn_error*/ turn_output * left_dir));
        }
        // should one of these subtract, maybe not becuase direction is + or -
        for (auto motor : right_motors)
        {
            motor.move(drive_output + (/*turn_error*/ turn_output * right_dir));
        }
        // delay
        pros::delay(kt::util::DELAY_TIME);
    } while ((!drive_pid_controller.goal_met() && distance != 0) || (!turn_pid_controller.goal_met()) /* && angle != 0*/);
    brake();
    move(0, endAngle, 1.0);
}

void kt::Chassis::drive_pid_constants(double drive_kP, double drive_kI, double drive_kD, double drive_range)
{
    // set pid const
    drive_pid_controller.set_pid_constants(drive_kP, drive_kI, drive_kD);
    drive_pid_controller.set_range(drive_range);
}

void kt::Chassis::turn_pid_constants(double turn_kP, double turn_kI, double turn_kD, double turn_range)
{
    // set pid const
    turn_pid_controller.set_pid_constants(turn_kP, turn_kI, turn_kD);
    turn_pid_controller.set_range(turn_range);
}

void kt::Chassis::drive_pid_constants(double drive_kP, double drive_kI, double drive_kD, double drive_range, int exit_time)
{
    // set pid const
    drive_pid_controller.set_pid_constants(drive_kP, drive_kI, drive_kD);
    drive_pid_controller.set_range(drive_range, exit_time);
}

void kt::Chassis::turn_pid_constants(double turn_kP, double turn_kI, double turn_kD, double turn_range, int exit_time)
{
    // set pid const
    turn_pid_controller.set_pid_constants(turn_kP, turn_kI, turn_kD);
    turn_pid_controller.set_range(turn_range, exit_time);
}

void kt::Chassis::move(int voltage)
{
    // move left motors
    for (auto motor : left_motors)
    {
        motor.move(voltage);
    }
    // move right motors
    for (auto motor : right_motors)
    {
        motor.move(voltage);
    }
}

void kt::Chassis::move(int voltage, int delay)
{
    // move left motors
    for (auto motor : left_motors)
    {
        motor.move(voltage);
    }
    // move right motors
    for (auto motor : right_motors)
    {
        motor.move(voltage);
    }
    pros::delay(delay);
    brake();
}

void kt::Chassis::turn(int voltage)
{
    // move left motors
    for (auto motor : left_motors)
    {
        motor.move(voltage);
    }
    // move right motors in oposite direction
    for (auto motor : right_motors)
    {
        motor.move(voltage * -1);
    }
}

void kt::Chassis::turn(int voltage, int delay)
{
    // move left motors
    for (auto motor : left_motors)
    {
        motor.move(voltage);
    }
    // move right motors
    for (auto motor : right_motors)
    {
        motor.move(voltage);
    }
    pros::delay(delay);
    brake();
}

void kt::Chassis::set_look_ahead_distance(double distance)
{
    look_ahead_distance = distance;
}

void kt::Chassis::opcontrol()
{
    // get the current value from the analog channel (-127 to 127)
    int ana_x = master.get_analog(controller_x_id);
    int ana_y = master.get_analog(controller_y_id);
    // check if its over the threshold
    ana_x = (abs(ana_x) > JOYSTICK_X_THRESHOLD) ? ana_x : 0;
    ana_y = (abs(ana_y) > JOYSTICK_Y_THRESHOLD) ? ana_y : 0;
    // if in tank control mode
    if (_tank_drive)
    {
        for (auto motor : left_motors)
        {
            motor.move(ana_x * JOYSTICK_X_SENSITIVITY);
        }
        for (auto motor : right_motors)
        {
            motor.move(ana_y * JOYSTICK_Y_SENSITIVITY);
        }
    }
    else
    { // if in any of the other control moves
        for (auto motor : left_motors)
        {
            motor.move(ana_y * JOYSTICK_Y_SENSITIVITY + ana_x * JOYSTICK_X_SENSITIVITY);
        }
        for (auto motor : right_motors)
        {
            motor.move(ana_y * JOYSTICK_Y_SENSITIVITY - ana_x * JOYSTICK_X_SENSITIVITY);
        }
        // if you are having issues with the direction of turning you can swap the plus and minus
    }
} // end of opcontrol function