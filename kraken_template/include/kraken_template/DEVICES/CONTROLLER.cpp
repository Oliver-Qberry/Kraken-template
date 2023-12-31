#pragma once
#include "main.h"
#include <tuple>

pros::Controller c_master(pros::E_CONTROLLER_MASTER);
pros::Controller c_partner(pros::E_CONTROLLER_PARTNER);

class _CONTROLLER {
    private:
        bool drive_keybinds_set = false;
        bool drive_sens_set = false;
        pros::controller_analog_e_t controller_analog_x_id;
        pros::controller_analog_e_t controller_analog_y_id;
        bool reverse_drive_direction;

        double x_multi;
        double y_multi;
    public:


        void set_drive_keybinds(pros::controller_analog_e_t controller_analog_x_id,
                                pros::controller_analog_e_t controller_analog_y_id,
                                bool reverse_drive_direction) {
            this->drive_keybinds_set = true;
            this->controller_analog_x_id = controller_analog_x_id;
            this->controller_analog_y_id = controller_analog_y_id;
            this->reverse_drive_direction = reverse_drive_direction;
        }

        void set_sensitivity(int x_multi, int y_multi) {
            this->drive_sens_set = true;
            this->x_multi = x_multi;
            this->y_multi = y_multi;
        }


        pros::Controller master() {return c_master;}
        pros::Controller partner() {return c_partner;}


        bool get_data_drive_keybinds_set() {return this->drive_keybinds_set;}
        bool get_data_drive_sens_set() {return drive_sens_set;}
        pros::controller_analog_e_t get_ana_x() {return this->controller_analog_x_id;}
        pros::controller_analog_e_t get_ana_y() {return this->controller_analog_y_id;}
        bool get_data_reverse_drive_direction() {return this->reverse_drive_direction;}
        double get_x_sensitivity() {return this->x_multi;}
        double get_y_sensitivity() {return this->y_multi;}
};