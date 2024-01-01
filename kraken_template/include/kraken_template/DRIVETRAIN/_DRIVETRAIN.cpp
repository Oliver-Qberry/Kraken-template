#pragma once
#include "main.h"

#include "DRIVE_MOTORS.cpp"
#include "kraken_template/pid/pid.cpp"

#include "kraken_template/framework.cpp"
#include "drivetrain_functions.cpp"
#include "kraken_template/DEVICES/device_functions/imu_functions.cpp"


#include <vector>

class _DRIVETRAIN {
    private:
        std::vector<pros::Motor> left_motors_vector;
        std::vector<pros::Motor> right_motors_vector;
        std::vector<pros::Imu> imu_vector;

        double gearset_rpm_ratio;
        double wheel_diameter;

        double drive_pid_karr[4];
        double turn_pid_karr[4];

    public:
        _DRIVE_MOTORS left_motors;
        _DRIVE_MOTORS right_motors;


        bool added_drivetrain_motors = false;
        bool added_drivetrain_imu = false;

        void set_motor_ports(std::vector<int> left_ports, std::vector<int> right_ports, 
                             pros::motor_brake_mode_e_t brake_type, bool reversed = false) {
            this->left_motors_vector.clear();
            this->right_motors_vector.clear();

            // reverse check
            bool lrb = (reversed) ? true : false;
            bool rrb = (reversed) ? false : true;

            // populate the motor vectors

            // maybe make this a function? //////////

            // left motors
            for (const auto& element : left_ports) {
                pros::Motor new_motor(element, lrb);
                new_motor.set_brake_mode(brake_type);
                this->left_motors_vector.push_back(new_motor);
            }
            this->left_motors = _DRIVE_MOTORS(left_motors_vector); // populate subclass
            // right motors
            for (const auto& element : right_ports) {
                pros::Motor new_motor(element, rrb); // right motors are reversed
                new_motor.set_brake_mode(brake_type);
                this->right_motors_vector.push_back(new_motor);
            }
            this->right_motors = _DRIVE_MOTORS(right_motors_vector);

            this->added_drivetrain_motors = true;
        }

        void set_rpm(double motor_rpm, double wheel_rpm, double wheel_diameter) {
            this->wheel_diameter = wheel_diameter;
            this->gearset_rpm_ratio = ((50.0)/((motor_rpm)/(3600.0)))*((motor_rpm)/(wheel_rpm));
        }

        void set_imu_port(int _port) {
            this->imu_vector.clear();
            pros::Imu new_imu(_port);
            this->imu_vector.push_back(new_imu);
            this->added_drivetrain_imu = true;
        }

        pros::Imu imu() {return imu_vector.front();}

        void set_drive_pid(double kp, double ki, double kd, double range) {
            this->drive_pid_karr[0] = kp; this->drive_pid_karr[1] = ki; this->drive_pid_karr[2] = kd; 
            this->drive_pid_karr[3] = range;
        }
        void set_turn_pid(double kp, double ki, double kd, double range) {
            this->turn_pid_karr[0] = kp; this->turn_pid_karr[1] = ki; this->turn_pid_karr[2] = kd; 
            this->turn_pid_karr[3] = range;
        }

        void move(double distance) {
            if (added_drivetrain_motors) {
                // create pid
                PIDController drive_pid(drive_pid_karr[0], drive_pid_karr[1], drive_pid_karr[2]);
                // reset pid
                drive_pid.reset();
                reset_drive_positions(left_motors, right_motors);
                // get distance
                double distanceIn = (((gearset_rpm_ratio*distance)/wheel_diameter))/2;
                drive_pid.set_goal(distanceIn, drive_pid_karr[3]);
                double current_pos, output;
                do {
                    current_pos = average_drive_positions(left_motors, right_motors);
                    output = drive_pid.calculate(current_pos);
                    left_motors.move(output);
		            right_motors.move(-output);
                    pros::delay(20);
                } while (!drive_pid.goal_met());
            }
        }

        void move(double distance, double angle) {
            if (added_drivetrain_motors && added_drivetrain_imu) {
                PIDController drive_pid(drive_pid_karr[0], drive_pid_karr[1], drive_pid_karr[2]);
                drive_pid.reset();
                reset_drive_positions(left_motors, right_motors);
                double distanceIn = (((gearset_rpm_ratio*distance)/wheel_diameter))/2;
                drive_pid.set_goal(distanceIn, drive_pid_karr[3]);
                double current_pos, drive_output;

                double target_angle = imu_vector.front().get_heading() + angle;
                PIDController turn_pid(turn_pid_karr[0], turn_pid_karr[1], turn_pid_karr[2]);
                turn_pid.reset();
                turn_pid.set_goal(0, turn_pid_karr[3]);
                double turn_error, turn_output;
                do {
                    current_pos = average_drive_positions(left_motors, right_motors);
                    drive_output = drive_pid.calculate(current_pos);
                    turn_error = imuErrorCalc(imu_vector.front().get_heading(), target_angle);
                    turn_output = turn_pid.calculate(turn_error);

                    //////////// NEED TO TEST ////////////

                    int left_dir = (charge(imuErrorCalc(imu_vector.front().get_heading(), target_angle)) > 0) ? -1 : 1;
                    int right_dir = (charge(imuErrorCalc(imu_vector.front().get_heading(), target_angle)) > 0) ? 1 : -1;

                    //////////// NEED TO TEST ////////////

                    left_motors.move(drive_output + (turn_error*left_dir));
                    right_motors.move(drive_output + (turn_error*right_dir));

                } while (!drive_pid.goal_met() || !turn_pid.goal_met());
            }
        }

        void turn(double angle) {
            if (added_drivetrain_imu) {
                double target_angle = imu_vector.front().get_heading() + angle;
            PIDController turn_pid(turn_pid_karr[0], turn_pid_karr[1], turn_pid_karr[2]);
            turn_pid.reset();
	        turn_pid.set_goal(0, turn_pid_karr[3]);
            double turn_error, output;
            do {
                turn_error = imuErrorCalc(imu_vector.front().get_heading(), target_angle);
                output = turn_pid.calculate(turn_error);
                left_motors.move(-output);
                right_motors.move(-output);

                pros::delay(20);
            } while (!turn_pid.goal_met());
            }
        }
};