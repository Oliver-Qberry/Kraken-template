#include "kt/drive/drive.hpp"
#include "kt/pid.hpp"
#include "kt/util.hpp"
#include "liblvgl/llemu.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include <string>

void kt::Chassis::initialize() {
    imu.reset();

}

kt::Chassis::Chassis(std::vector<int> left_motor_ports, std::vector<int> right_motor_ports,
                    pros::motor_brake_mode_e_t brake_type, 
                    int imu_port, 
                    double motor_rpm, double wheel_rpm, double wheel_diameter) : 
                    imu(imu_port), 
                    motor_rpm(motor_rpm), wheel_rpm(wheel_rpm), wheel_diameter(wheel_diameter) {
    for (auto i : left_motor_ports) {
        pros::Motor motor(abs(i));
        motor.set_reversed(kt::util::reversed_active(i));
        motor.set_brake_mode(brake_type);
        left_motors.push_back(motor);
    }
    for (auto i : right_motor_ports) {
        pros::Motor motor(abs(i));
        motor.set_reversed(kt::util::reversed_active(i));
        right_motors.push_back(motor);
    }
}



void kt::Chassis::opcontrol_tank() {
    _tank_drive = true;
    controller_x_id = pros::E_CONTROLLER_ANALOG_LEFT_Y; // 
    controller_y_id = pros::E_CONTROLLER_ANALOG_RIGHT_Y;
}

void kt::Chassis::opcontrol_arcade_standard() {
    _tank_drive = false;
    controller_x_id = pros::E_CONTROLLER_ANALOG_LEFT_X;
    controller_y_id = pros::E_CONTROLLER_ANALOG_LEFT_Y;
}

void kt::Chassis::opcontrol_arcade_flipped() {
    _tank_drive = false;
    controller_x_id = pros::E_CONTROLLER_ANALOG_RIGHT_X;
    controller_y_id = pros::E_CONTROLLER_ANALOG_RIGHT_Y;
}

void kt::Chassis::opcontrol_split_standard() {
    _tank_drive = false;
    controller_x_id = pros::E_CONTROLLER_ANALOG_RIGHT_X;
    controller_y_id = pros::E_CONTROLLER_ANALOG_LEFT_Y; //
}

void kt::Chassis::opcontrol_split_flipped() {
    _tank_drive = false;
    controller_x_id = pros::E_CONTROLLER_ANALOG_LEFT_X;
    controller_y_id = pros::E_CONTROLLER_ANALOG_RIGHT_Y;
}

void kt::Chassis::reset_integrated_encoders() {
    for (auto motor : left_motors) {
        motor.set_zero_position(0);
    }
    for (auto motor : right_motors) {
        motor.set_zero_position(0);
    }
}

double kt::Chassis::get_average_integrated_encoders_positions() {
    double left_sum = 0;
    for (auto motor : left_motors) {
        left_sum += motor.get_position();
    }
    double left_avg = left_sum/left_motors.size();
    double right_sum = 0;
    for(auto motor : right_motors) {
        right_sum += motor.get_position();
    }
    double right_avg = right_sum/right_motors.size();
    return (left_avg + right_avg)/2;
}


void kt::Chassis::brake() {
    for (auto motor : left_motors) {
        motor.brake();
    }
    for (auto motor : left_motors) {
        motor.brake();
    }
}




// NEEDS TO BE TESTED MORE
void kt::Chassis::move(double distance, double angle) {
    // setup drive pid
    drive_pid_controller.reset();
    reset_integrated_encoders();
    double gearset_rpm_ratio = ((50.0)/((motor_rpm)/(3600.0)))*((motor_rpm)/(wheel_rpm));
    double distanceIn = (((gearset_rpm_ratio*distance)/wheel_diameter))/2;
    drive_pid_controller.set_goal(distanceIn, drive_pid_karr[3]);
    double current_pos, drive_output;
    // setup turn pid
    double target_angle = imu.get_heading() + angle;
    turn_pid_controller.reset();
    turn_pid_controller.set_goal(0, turn_pid_karr[3]);
    double turn_error, turn_output;
    int left_dir, right_dir;
    // pid loop
    do {
        current_pos = get_average_integrated_encoders_positions();
        drive_output = drive_pid_controller.calculate(current_pos);
        turn_error = kt::util::imu_error_calc(imu.get_heading(), target_angle);
        turn_output = turn_pid_controller.calculate(turn_error);
        //////////////// TEST
        left_dir = (kt::util::sgn(kt::util::imu_error_calc(imu.get_heading(), target_angle)) > 0) ? -1 : 1;
        right_dir = (kt::util::sgn(kt::util::imu_error_calc(imu.get_heading(), target_angle)) > 0) ? 1 : -1;
        ///////////////// TEST
        // MAY NOT NEED THE ABOVE STUFF
        for (auto motor : left_motors) {
            motor.move(drive_output + (turn_error*left_dir));
        }
        for (auto motor : right_motors) {
            motor.move(drive_output + (turn_error*right_dir));
        }

        /////////////////////////////////////////////////////
        // add a system to get error in the system
        /////////////////////////////////////////////////////
        //std::cout<<drive_output<<std::endl;
        //pros::lcd::set_text(4, std::to_string(turn_error));

        pros::delay(kt::util::DELAY_TIME);
    } while (!drive_pid_controller.goal_met() || !turn_pid_controller.goal_met());
    brake();
}


void kt::Chassis::drive_pid_constants(double drive_kP, double drive_kI, double drive_kD, double drive_range) {
    drive_pid_controller.set_pid_constants(drive_kP, drive_kI, drive_kD);
    drive_pid_controller.set_range(drive_range);
}

void kt::Chassis::turn_pid_constants(double turn_kP, double turn_kI, double turn_kD, double turn_range) {
    turn_pid_controller.set_pid_constants(turn_kP, turn_kI, turn_kD);
    turn_pid_controller.set_range(turn_range);
}











void kt::Chassis::move(int voltage) {
    for (auto motor : left_motors) {
        motor.move(voltage);
    }
    for (auto motor : left_motors) {
        motor.move(voltage);
    }
}

void kt::Chassis::turn(int voltage) {
    for (auto motor : left_motors) {
        motor.move(voltage);
    }
    for (auto motor : left_motors) {
        motor.move(voltage * -1);
    }
}

void kt::Chassis::opcontrol() {
        int ana_x = master.get_analog(controller_x_id); // 
        int ana_y = master.get_analog(controller_y_id);
        ana_x = (abs(ana_x) > JOYSTICK_X_THRESHOLD) ? ana_x : 0;
        ana_y = (abs(ana_y) > JOYSTICK_Y_THRESHOLD) ? ana_y : 0;
    if (_tank_drive) {

        for (auto motor : left_motors) {
            motor.move(ana_x*JOYSTICK_X_SENSITIVITY);
        }
        for (auto motor : right_motors) {
            motor.move(ana_y*JOYSTICK_Y_SENSITIVITY);
        }
    } else {
        for (auto motor : left_motors) {
            motor.move(ana_y*JOYSTICK_Y_SENSITIVITY-ana_x*JOYSTICK_X_SENSITIVITY);
        }
        for (auto motor : right_motors) {
            motor.move(ana_y*JOYSTICK_Y_SENSITIVITY+ana_x*JOYSTICK_X_SENSITIVITY);
        }
    }
}