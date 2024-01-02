#pragma once
#include "main.h"

#include <string>
#include <vector>

class Node_ADIDigitalIn {
    public:
        std::string _name;
        std::vector<pros::ADIDigitalIn> adiin;
        bool has_adv_data = false;
        pros::controller_digital_e_t _keybind;
        bool _in_toggle_mode;
        bool _reverse_flow;

        Node_ADIDigitalIn (std::string _name, char _port) {
            this->_name = _name;
            pros::ADIDigitalIn new_adiin(_port);
            this->adiin.clear();
            this->adiin.push_back(new_adiin);
        }

        void set_data(pros::controller_digital_e_t _keybind, bool _in_toggle_mode, bool _reverse_flow) {
            this->_keybind = _keybind;
            this->_in_toggle_mode = _in_toggle_mode;
            this->_reverse_flow = _reverse_flow;

            this->has_adv_data = true;
        }

        pros::ADIDigitalIn get_adiin() {return adiin.front();}
};