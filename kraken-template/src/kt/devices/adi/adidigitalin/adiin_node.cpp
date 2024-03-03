#include "kt/devices/adi/adidigitalin/adiin_node.hpp"

adidigitalin_node::adidigitalin_node(std::string _name, char _port) {
    this->_name = _name;
    pros::adi::DigitalIn new_adiin(_port);
    adiin.clear();
    adiin.push_back(new_adiin);
}

adidigitalin_node::adidigitalin_node(std::string _name, char _port, 
                                     kt::e_bool _target_bool, kt::e_press_type _press_type, 
                                     void(*_function)()) {
    this->_name = _name;
    pros::adi::DigitalIn new_adiin(_port);
    adiin.clear();
    adiin.push_back(new_adiin);
    this->_target_bool = _target_bool;
    this->_press_type = _press_type;
    this->_function = _function;
    this->_has_data_for_opc = true;
}

void adidigitalin_node::opcontrol() {
    if (_has_data_for_opc) {
        if (_press_type == kt::e_press_type::ON_NEW_PRESS) {
            // on new press
            if (_target_bool == adiin.front().get_new_press()) {
                _function();
            }
        } else {
            // on press
            if (_target_bool == adiin.front().get_value()) {
                _function();
            }
        }
    }
} // end of opcontrol function