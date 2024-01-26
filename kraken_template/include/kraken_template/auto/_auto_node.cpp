//#pragma once
#include "main.h"
#include <string>

class auto_node{
    private:
    public:
        void (*_function)();
        std::string _desc;

        auto_node() {}
        auto_node(void (*_function)(), std::string _desc) {
            this->_function = _function;
            this->_desc = _desc;
        }

        void run() {_function();}
};