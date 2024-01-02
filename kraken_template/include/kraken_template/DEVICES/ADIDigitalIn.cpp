#pragma once
#include "main.h"

#include "nodes/ADIDigitalIn_Node.cpp"
#include <string>
#include <unordered_map>
#include <vector>

class _ADIDigitalIn {
    private:
        std::vector<std::string> node_names;
        std::unordered_map<std::string, Node_ADIDigitalIn> node_map;

    public:
        bool added_adi = false;

        void new_ADI(std::string name, char port) {
            this->node_names.push_back(name);
            Node_ADIDigitalIn node(name, port);
            this->node_map[name] = node;
            this->added_adi = true;
        }

        void set_ADI_keybinds(std::string name, pros::controller_digital_e_t keybind, 
                               bool in_toggle_mode = false, bool reverse_flow = false) {
            this->node_map[name].set_data(keybind, in_toggle_mode, reverse_flow);
        }

        pros::ADIDigitalIn get_ADI(std::string name) {
            return node_map[name].get_adiin();
        }

        std::vector<std::string> get_ADI_names() {
            return node_names;
        }

        Node_ADIDigitalIn get_ADI_node(std::string name) {
            return node_map[name];
        }
};