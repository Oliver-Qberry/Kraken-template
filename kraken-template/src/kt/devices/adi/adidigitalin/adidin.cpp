#include "kt/devices/adi/adidigitalin/adidin.hpp"

void kt::ADI_DIGITALIN::new_adi(std::string name, char port) {
    adidigitalin_node node(name, port);
    node_map[name] = node;
}

void kt::ADI_DIGITALIN::new_adi(std::string name, char port, 
                                kt::e_bool target_bool, kt::e_press_type press_type, 
                                void(*function)()) {
    adidigitalin_node node(name, port, target_bool, press_type, function);
    node_map[name] = node;
}

pros::adi::DigitalIn kt::ADI_DIGITALIN::get_adi(std::string name) {
    return node_map[name].adiin.front();
}

void kt::ADI_DIGITALIN::opcontrol(std::string name) {
    node_map[name].opcontrol();
}