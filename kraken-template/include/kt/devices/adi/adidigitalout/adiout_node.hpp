#pragma once

#include "kt/util.hpp"
#include "pros/adi.hpp"
#include "pros/misc.h"

#include <string>
#include <vector>

// class for handling each adi digital out node
class adidigitalout_node {

    public:

    // node name
    std::string _name;

    // nodes adi digital out
    std::vector<pros::adi::DigitalOut> adiout;

    // nodes keybind
    pros::controller_digital_e_t _keybind;

    // nodes press type
    kt::e_press_type _press_type;

    // nodes toggle mode
    bool _toggle_mode;

    // nodes reverse bool
    bool _reverse;
    
    // is sending data bool
    bool _current_sending_data;

    // has data for opcontrol bool
    bool _has_data_for_opc = false;

    // base constructor
    adidigitalout_node() {}

    // constructor with no complex info
    adidigitalout_node(std::string _name, char _port);

    // constructor with complex info (for opc function)
    adidigitalout_node(std::string _name, char _port,
                       pros::controller_digital_e_t _keybind, kt::e_press_type _press_type,
                       kt::e_toggle_mode _toggle_mode, bool _reverse);

    // general opc function. must have enough data
    void opcontrol();
}; // end of adidigitalout_node class