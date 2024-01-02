#pragma once
#include "main.h"
#include <string>
#include <vector>

class Node_ADIDigitalOut {
    private:
    public:
        std::string _name;
        std::vector<pros::ADIDigitalOut> adiout;
        bool has_adv_data = false;
        pros::controller_digital_e_t _keybind;
        bool _in_toggle_mode;
        bool _reverse_flow;

        bool _current_toggle = false;

        Node_ADIDigitalOut (std::string _name, char _port) {
            this->_name = _name;
            pros::ADIDigitalOut new_adiin(_port);
            this->adiout.clear();
            this->adiout.push_back(new_adiin);
        }

        void set_data(pros::controller_digital_e_t _keybind, bool _in_toggle_mode, bool _reverse_flow) {
            this->_keybind = _keybind;
            this->_in_toggle_mode = _in_toggle_mode;
            this->_reverse_flow = _reverse_flow;

            // proactive setup of current toggle
            // used in opc in the get new press to determine value
            if (_reverse_flow) {
                this->_current_toggle = true;
            }

            this->has_adv_data = true;
        }

        pros::ADIDigitalOut get_adiout() {return adiout.front();}

        void toggle_current_toggle() {
            this->_current_toggle = (this->_current_toggle) ? false : true;
        }
};