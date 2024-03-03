#include "config.hpp"
#include "kt/util.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include <string>

using namespace pros;
using namespace kt;
using namespace v5;





void initialize_devices() {
// define your devices here using their subclasses for them to be brought to both auton and main files
lcd::initialize();


}

void print_to_lcd_task() {
    while (true) {
        lcd::set_text(0, "2605A Kraken");
        lcd::set_text(1, autons.current_name());
        lcd::set_text(2, autons.current_desc());
        lcd::set_text(3, std::to_string(chassis.imu.get_heading()));
        
        pros::delay(kt::util::DELAY_TIME);
    }
}