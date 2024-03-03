#pragma once

#include "kt/util.hpp"
#include "kt/devices/adi/adidigitalout/adiout_node.hpp"

#include <string>
#include <unordered_map>

namespace kt {
// class to store and handle adi digital outputs
class ADI_DIGITALOUT {

    private:
    // map of store adi d out nodes
    std::unordered_map<std::string, adidigitalout_node> node_map;

    public:
    // add a new adi digital output to the handler class (non complex)
    void new_adi(std::string name, char port);

    // add new adi digital output to the handler class (complex).
    /*
    parameters:
        the inputs name.
        the inputs port.
        the controller keybind.
        the controller press type.
        the toggle mode.
        if it should in reverse mode.
    */
    void new_adi(std::string name, char port,
                 pros::controller_digital_e_t keybind, kt::e_press_type press_type,
                 kt::e_toggle_mode toggle_mode, bool reverse);

    // get an adi digital output from the handler via its name
    pros::adi::DigitalOut get_adi(std::string name);

    // run the adi digital output opc function
    void opcontrol(std::string name);

}; // end of ADI_DIGITALOUT class
} // end of kt namespace