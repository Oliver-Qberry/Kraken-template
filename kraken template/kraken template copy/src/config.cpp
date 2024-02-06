#include "config.hpp"
#include "kt/util.hpp"
#include "pros/misc.h"
#include "pros/motors.h"

using namespace pros;
using namespace kt;
using namespace v5;

void func() {
    std::cout<<"test"<<std::endl;
}



void initialize_devices() {
// define your devices here using their subclasses for them to be brought to both auton and main files

motor.new_motor("intake", -18, 
                E_CONTROLLER_DIGITAL_R1, ON_PRESS, 
                E_CONTROLLER_DIGITAL_R2, ON_PRESS
                );


motor.new_motor("fly", 19, MotorGears::blue, 300, {1, 0, 0}, 0);

AdiDigitalOut.new_adi("test", 'a', pros::E_CONTROLLER_DIGITAL_A, e_press_type::ON_NEW_PRESS, e_toggle_mode::IN_TOGGLE_MODE, false);


}