#pragma once
#include "main.h"

#include <string>
#include <vector>

class Node_ADIDigitalIn {
    public:
        std::string _name;
        std::vector<pros::ADIDigitalIn> adiin;
        bool has_adv_data = false;
        bool _reverse_flow;
        bool _on_new_press;
        void (*_function)();

        Node_ADIDigitalIn (std::string _name, char _port) {
            this->_name = _name;
            pros::ADIDigitalIn new_adiin(_port);
            this->adiin.clear();
            this->adiin.push_back(new_adiin);
        }

        void set_data(void (*_function)(), bool _reverse_flow, bool _on_new_press) {
            this->_function = _function;
            this->_reverse_flow = _reverse_flow;
            this->_on_new_press = _on_new_press;
            this->has_adv_data = true;
        }

        pros::ADIDigitalIn get_adiin() {return adiin.front();}

        void run() {_function();}
};