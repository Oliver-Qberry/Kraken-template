//#pragma once
#include "main.h"

#include "_auto_node.cpp"

#include <array>
#include <string>
#include <unordered_map>
#include <vector>

class _AUTO {
    private:
        std::string default_auto_name;
        bool has_default_auto = false;
        std::vector<std::string> node_names;
        std::string* name_arr;
        std::unordered_map<std::string, auto_node> node_map;
        pros::controller_digital_e_t _keybind;
        int num_of_autos = 0;
    public:
        bool has_adv_data = false;
        int auto_select = 0;

        void new_auto(std::string name, std::string desc, void(*function)()) {
            this->node_map[name] = auto_node(function, desc);
            this->num_of_autos += 1;
        }

        void set_default_auto(std::string name) {
            this->default_auto_name = name;
            this->has_default_auto = true;
        }

        void set_auto_select_keybind(pros::controller_digital_e_t _keybind) {
            this->_keybind = _keybind;
            this->has_adv_data = true;
        }

        void run_auto(std::string name) {
            this->node_map[name].run();
        }

        pros::controller_digital_e_t keybind() {
            return this->_keybind;
        }

        int len() {
            return this->num_of_autos;
        }

        void generate_name_array() {
            std::string* arr = new std::string[this->num_of_autos];

            int i = 0;

            if (this->has_default_auto) {
                arr[i] = this->default_auto_name;
                i += 1;
            }

            for (auto& name : this->node_names) {
                if (this->has_default_auto == true) {
                    if (name != this->default_auto_name) {
                        arr[i] = name;
                    }
                } else {
                    arr[i] = name;
                }
                i += 1;
            }
            this->name_arr = arr;
        }

        std::string* get_name_array() {return this->name_arr;}

        std::unordered_map<std::string, auto_node> get_map() {return node_map;}
    
        //~_AUTO() {
        //    delete[] generate_name_array();
        //}
};