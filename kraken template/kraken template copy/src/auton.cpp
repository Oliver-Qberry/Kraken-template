#include "auton.hpp"
#include "kt/util.hpp"
#include "pros/motors.h"
#include "pros/rtos.hpp"

void test1() {
    std::cout<<"test1"<<std::endl;
    chassis.CURRENT_BRAKE = pros::E_MOTOR_BRAKE_HOLD;
    chassis.drive_pid_constants(.5, 0, 0, 1);
    chassis.turn_pid_constants(1, 0, 0, 10);
    chassis.move(5, 90);
}
void test2() {
    std::cout<<"test2"<<std::endl;
}

void test3() {
    std::cout<<"test3"<<std::endl;
}


void initialize_auton() {
    autons.add_auton("test1", "d1", test1);
    autons.add_auton("test2", "d2", test2);
    autons.add_auton("test3", "d3", test3);
}

void initialize_task() {
    while (true) {
        autons.initialize();
        pros::lcd::set_text(3, std::to_string(chassis.imu.get_heading()));
        pros::delay(kt::util::DELAY_TIME);
    }
}