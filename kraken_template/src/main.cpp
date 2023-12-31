#include "main.h"

//#include "config.cpp"
#include "kraken_template/_opc.cpp"

void initialize() {}

void competition_initialize() {}


void autonomous() {}

void opcontrol() {
    while (true) {

        opc._adi();

        opc._motor();

        opc._drivetrain();

        pros::delay(20);
    }
}

void disabled() {}