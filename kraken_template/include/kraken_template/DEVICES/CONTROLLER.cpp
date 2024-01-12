#pragma once
#include "main.h"

#include "nodes/CONTROLLER_Node.cpp"

pros::Controller c_master(pros::E_CONTROLLER_MASTER);
pros::Controller c_partner(pros::E_CONTROLLER_PARTNER);

/*
setup a data node
*/

class _CONTROLLER {
    private:
    public:
        Node_CONTROLLER_DATA data;

        void set_drive_keybinds(pros::controller_analog_e_t controller_analog_x_id,
                                pros::controller_analog_e_t controller_analog_y_id,
                                bool reverse_drive_direction) {
            data.set_drive_data(controller_analog_x_id, controller_analog_y_id, reverse_drive_direction);
        }

        void set_sensitivity(int x_sensitivity, int y_sensitivity) {
            data.set_sensitivity_data(x_sensitivity, y_sensitivity);
        }

        pros::Controller master() {return c_master;}
        pros::Controller partner() {return c_partner;}
};