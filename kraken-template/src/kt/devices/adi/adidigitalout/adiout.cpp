#include "kt/devices/adi/adidigitalout/adiout.hpp"

void kt::ADI_DIGITALOUT::new_adi(std::string name, char port) {
    adidigitalout_node node(name, port);
    node_map[name] = node;
}

void kt::ADI_DIGITALOUT::new_adi(std::string name, char port,
             pros::controller_digital_e_t keybind, kt::e_press_type press_type,
             kt::e_toggle_mode toggle_mode, bool reverse) {
    adidigitalout_node node(name, port, keybind, press_type, toggle_mode, reverse);
    node_map[name] = node;
}

pros::adi::DigitalOut kt::ADI_DIGITALOUT::get_adi(std::string name) {
    return node_map[name].adiout.front();
}

void kt::ADI_DIGITALOUT::opcontrol(std::string name) {
    node_map[name].opcontrol();
}