#pragma once

#include "kt/util.hpp"
#include "kt/devices/adi/adidigitalin/adiin_node.hpp"

#include <string>
#include <unordered_map>

namespace kt {


class ADI_DIGITALIN {
    private:
    std::unordered_map<std::string, adidigitalin_node> node_map;
    public:

    void new_adi(std::string name, char port) {
        adidigitalin_node node(name, port);
        node_map[name] = node;
    }

    void new_adi(std::string name, char port, 
                      kt::e_bool target_bool, kt::e_press_type press_type, 
                      void(*function)()) {
        adidigitalin_node node(name, port, target_bool, press_type, function);
        node_map[name] = node;
    }

    pros::adi::DigitalIn get_adi(std::string name) {
        return node_map[name].adiin.front();
    }

    void opcontrol(std::string name) {
        node_map[name].opcontrol();
    }
};
}