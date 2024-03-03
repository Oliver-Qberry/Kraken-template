#pragma once

#include "kt/util.hpp"
#include "pros/adi.hpp"
#include "pros/misc.h"

#include <string>
#include <vector>

// class for handling each adi digital in node
class adidigitalin_node {

    public:

    // nodes name
    std::string _name;

    // nodes adi digial in
    std::vector<pros::adi::DigitalIn> adiin;

    // nodes target bool
    bool _target_bool;

    // nodes press type
    kt::e_press_type _press_type;

    // nodes callback function
    void(*_function)();

    // if node has enough data for the opc function
    bool _has_data_for_opc = false;

    // base constructor for the node
    adidigitalin_node() {}; // might need to change
    // if giving issues change to a vector and grab the front / clear and append
    
    // constructor with no complex info
    adidigitalin_node(std::string _name, char _port);

    // constructor with complex info (for opc function)
    adidigitalin_node(std::string _name, char _port, 
                      kt::e_bool _target_bool, kt::e_press_type _press_type, 
                      void(*_function)());

    // general opc function. must have enough data
    void opcontrol();
    
}; // end of adidigitalin_node class