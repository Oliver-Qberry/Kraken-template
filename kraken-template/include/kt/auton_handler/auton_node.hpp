#pragma once

#include <string>

/*
class to store info about an auton node.
node has the auton name, description, and its function, and the means to call its function
*/
class auton_node {
    public:
    // auton name
    std::string _name;
    // auton description
    std::string _desc;
    // auton function
    void(*_function)();
    // constructor
    auton_node(std::string _name, std::string _desc, void(*_function)()) {
        this->_name = _name;
        this->_desc = _desc;
        this->_function = _function;
    }

    // function to properly run the stored auton function
    void run();
    
}; // end of auton_node class