#pragma once

#include "kt/util.hpp"
#include "kt/devices/adi/adidigitalin/adiin_node.hpp"

#include <string>
#include <unordered_map>

namespace kt {
// class to store and handle adi digital inputs
class ADI_DIGITALIN {

    private:
    // map of store adi d in nodes
    std::unordered_map<std::string, adidigitalin_node> node_map;

    public:
    // add a new adi digital input to the handler class (non complex)
    void new_adi(std::string name, char port);

    // add new adi digital input to the handler class (complex).
    /*
    parameters:
        the inputs name.
        the inputs port.
        the target bool (the bool to look for during opc).
        the type of press the input will look for.
        the function that will be called when the target bool is reached.
    */
    void new_adi(std::string name, char port, 
                      kt::e_bool target_bool, kt::e_press_type press_type, 
                      void(*function)());

    // get an adi digital input from the handler via its name
    pros::adi::DigitalIn get_adi(std::string name);

    // run the adi digital inputs opc function
    void opcontrol(std::string name);

}; // end of ADI_DIGIALIN class
} // end of kt namespace