#pragma once

#include "kt/util.hpp"
#include "pros/adi.hpp"
#include "pros/misc.h"

#include <string>
#include <vector>
class adidigitalout_node {
    public:
    std::string _name;
    std::vector<pros::adi::DigitalOut> adiout;

    pros::controller_digital_e_t _keybind;
    kt::e_press_type _press_type;

    bool _toggle_mode;
    bool _reverse;
    
    bool _current_sending_data;
    bool _has_data_for_opc = false;

    adidigitalout_node() {}

    adidigitalout_node(std::string _name, char _port) {
        this->_name = _name;
        pros::adi::DigitalOut new_adi(_port);
        adiout.clear();
        adiout.push_back(new_adi);
    }
    adidigitalout_node(std::string _name, char _port,
                       pros::controller_digital_e_t _keybind, kt::e_press_type _press_type,
                       kt::e_toggle_mode _toggle_mode, bool _reverse) {
        this->_name = _name;
        pros::adi::DigitalOut new_adi(_port);
        adiout.clear();
        adiout.push_back(new_adi);
        this->_keybind = _keybind;
        this->_press_type = _press_type;

        this->_toggle_mode = _toggle_mode;
        this->_reverse = _reverse;

        this->_current_sending_data = (_reverse) ? true : false;
        this->_has_data_for_opc = true;
    }

    void opcontrol() {
        if (_has_data_for_opc) {
            if (_press_type == kt::ON_NEW_PRESS) {
                // on new press
                if (master.get_digital_new_press(_keybind)) {
                    _current_sending_data = (_current_sending_data) ? false : true;
                }
                adiout.front().set_value(_current_sending_data);
            } else {
                // on press
                if (master.get_digital_new_press(_keybind)) {
                    _current_sending_data = (_reverse) ? false : true;
                } else {
                    _current_sending_data = (_reverse) ? true : false;
                }
                adiout.front().set_value(_current_sending_data);
            }
        }
    }
};