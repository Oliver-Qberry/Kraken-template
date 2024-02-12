#include "config.hpp"
#include "kt/util.hpp"
#include "pros/misc.h"
#include "pros/motors.h"

using namespace pros;
using namespace kt;
using namespace v5;





void initialize_devices() {
// define your devices here using their subclasses for them to be brought to both auton and main files



}

void print_to_lcd_task() {
    while (true) {
        pros::delay(kt::util::DELAY_TIME);
    }
}