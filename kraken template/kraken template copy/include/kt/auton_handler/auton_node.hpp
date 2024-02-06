#pragma once
#include <string>
class auton_node {
    private:
    public:
    std::string _name;
    std::string _desc;
    void(*_function)();
    auton_node(std::string _name, std::string _desc, void(*_function)()) {
        this->_name = _name;
        this->_desc = _desc;
        this->_function = _function;
    }
    void run() {_function();}
};