#pragma once
#include "main.h"

#include "nodes/ADIDigitalOut_Node.cpp"
#include <string>
#include <unordered_map>
#include <vector>

class _ADIDigitalOut {
    private:
        std::vector<std::string> node_names;
        std::unordered_map<std::string, Node_ADIDigitalOut> node_map;

    public:
        bool added_adi = false;

        void new_ADI(std::string name, char port) {
            Node_ADIDigitalOut node(name, port);
            this->node_names.push_back(name);
            this->node_map[name] = node;
            this->added_adi = true;
        }

        void set_ADI_keybinds(std::string name, pros::controller_digital_e_t keybind, 
                               bool in_toggle_mode = false, bool reverse_flow = false) {
            this->node_map[name].set_data(keybind, in_toggle_mode, reverse_flow);
        }

        pros::ADIDigitalOut get_ADI(std::string name) {
            return node_map[name].get_adiout();
        }

        std::vector<std::string> get_ADI_names() {
            return node_names;
        }

        Node_ADIDigitalOut get_ADI_node(std::string name) {
            return node_map[name];
        }
};