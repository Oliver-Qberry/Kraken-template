// ==================== include ==================== //
// main header for c++ and pros
#include "main.h"
// kraken template include
// main config include
#include "config.cpp"
// opc function include
#include "kraken_template/_opc.cpp"

// ==================== initialize functions ==================== //
void initialize() {
    config(); 
    setup_on_startup();

    pros::lcd::set_text(1, "kraken template: auto select");

    while (true) {
        if (AUTO.has_adv_data) {
            if (devices.controller.master().get_digital_new_press(AUTO.keybind())) {
                AUTO.auto_select += 1;
                if (AUTO.auto_select >= AUTO.len()) {
                    AUTO.auto_select = 0;
                }
            }
        }
        pros::lcd::set_text(2, AUTO.get_map()[AUTO.get_name_array()[AUTO.auto_select]]._desc);
        pros::delay(20);
    }
}

void competition_initialize() {when_competition_initialize();}

 // ==================== match control functions ==================== //
 // autonomous function
void autonomous() {AUTO.get_map()[AUTO.get_name_array()[AUTO.auto_select]].run();}

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
void disabled() {when_disabled();}