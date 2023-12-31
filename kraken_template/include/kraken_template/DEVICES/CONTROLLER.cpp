#pragma once
#include "main.h"
#include <tuple>

pros::Controller c_master(pros::E_CONTROLLER_MASTER);
pros::Controller c_partner(pros::E_CONTROLLER_PARTNER);

class _CONTROLLER {
    public:
        bool drive_keybinds_set = false;
        pros::controller_analog_e_t controller_analog_x_id;
        pros::controller_analog_e_t controller_analog_y_id;
        bool reverse_drive_direction;

        std::tuple<int, int> sensitivity;


        void set_drive_keybinds(pros::controller_analog_e_t controller_analog_x_id,
                                pros::controller_analog_e_t controller_analog_y_id,
                                bool reverse_drive_direction) {
            this->drive_keybinds_set = true;
            this->controller_analog_x_id = controller_analog_x_id;
            this->controller_analog_y_id = controller_analog_y_id;
            this->reverse_drive_direction = reverse_drive_direction;
        }

        void set_sensitivity(int x_multi, int y_multi) {
            std::tuple<int, int> new_sens = {x_multi, y_multi};
            this->sensitivity = new_sens;
        }


        pros::Controller master() {return c_master;}
        pros::Controller partner() {return c_partner;}


        bool get_data_drive_keybinds_set() {return this->drive_keybinds_set;}
        pros::controller_analog_e_t get_ana_x() {return this->controller_analog_x_id;}
        pros::controller_analog_e_t get_ana_y() {return this->controller_analog_y_id;}
        bool get_data_reverse_drive_direction() {return this->reverse_drive_direction;}
        std::tuple<int, int> get_sensitivity() {return this->sensitivity;}
};