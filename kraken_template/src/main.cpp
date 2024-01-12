// ==================== include ==================== //
// main header for c++ and pros
#include "main.h"
// kraken template include
#include "config.cpp"
#include "kraken_template/_opc.cpp"

// ==================== initialize functions ==================== //
void initialize() {
    config(); 
    setup_on_startup();

    while (true) {
        
    }
}

void competition_initialize() {}

 // ==================== match control functions ==================== //
 // autonomous function
void autonomous() {}

// operator control function
void opcontrol() {
    // ==================== main operator control loop ==================== //
    while (true) {
        // ==================== stock adi in control ==================== //
        opc._adi_in();
        // ==================== stock adi out control ==================== //
        opc._adi_out();
        // ==================== stock motor control ==================== //
        opc._motor();
        // ==================== stock drive control ==================== //
        opc._drivetrain();

        // make sure that your opc loop has a slight delay
        pros::delay(20);
    }
}

// robot disabled function
void disabled() {}