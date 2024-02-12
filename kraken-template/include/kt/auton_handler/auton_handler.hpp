#pragma once

#include "kt/auton_handler/auton_node.hpp"
#include "kt/util.hpp"
#include <string>
#include <vector>

namespace kt {
class AUTONS {
private:
    int auto_select = 0;
    int auto_select_type;
    pros::controller_digital_e_t controller_keybind;

public:
    AUTONS(pros::controller_digital_e_t controller_keybind) {
        this->auto_select_type = 0;
        this->controller_keybind = controller_keybind;
    }

    int number_of_autos_saved = 0;
    std::vector<auton_node> auton_node_vector;

    void add_auton(std::string name, std::string description, void(*function)()) {
        auton_node node(name, description, function);
        this->auton_node_vector.push_back(node);
        this->number_of_autos_saved += 1;
    }

    void increment() {
        auto_select += 1;
        if (auto_select >= auton_node_vector.size()) {
            auto_select = 0;
        }
    }

    std::string current_name() {return auton_node_vector[auto_select]._name;}
    std::string current_desc() {return auton_node_vector[auto_select]._desc;}
    void run_current_auton() {auton_node_vector[auto_select].run();}


    void auton_select_task() {
        if (auto_select_type == 0) {
            // controller
            if (master.get_digital_new_press(controller_keybind)) {
                increment();
            }
        }
    }
};
}