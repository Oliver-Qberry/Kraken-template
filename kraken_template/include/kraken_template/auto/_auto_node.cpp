//#pragma once
#include "main.h"
#include <string>

class auto_node{
    private:
    public:
        int _function;
        std::string _desc;

        auto_node() {}
        auto_node(int _function, std::string _desc) : _function(_function), _desc(_desc) {}

        int run() {
            return _function;
        }
};