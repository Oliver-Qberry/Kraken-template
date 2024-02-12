#pragma once

#include "kt/util.hpp"
#include "kt/devices/adi/adidigitalout/adiout_node.hpp"

#include <string>
#include <unordered_map>

namespace kt {
class ADI_DIGITALOUT {
    private:
    std::unordered_map<std::string, adidigitalout_node> node_map;
    public:

    void new_adi(std::string name, char port) {
        adidigitalout_node node(name, port);
        node_map[name] = node;
    }

    void new_adi(std::string name, char port,
                 pros::controller_digital_e_t keybind, kt::e_press_type press_type,
                 kt::e_toggle_mode toggle_mode, bool reverse) {
        adidigitalout_node node(name, port, keybind, press_type, toggle_mode, reverse);
        node_map[name] = node;
    }

    pros::adi::DigitalOut get_adi(std::string name) {
        return node_map[name].adiout.front();
    }

    void opcontrol(std::string name) {
        node_map[name].opcontrol();
    }
};
}