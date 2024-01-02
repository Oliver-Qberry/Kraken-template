#pragma once
#include "main.h"
#include <string>
#include <vector>

class Node_ROTATION {
    public:
        std::string _name;
        std::vector<pros::Rotation> rot;


        Node_ROTATION (std::string _name, char _port) {
            this->_name = _name;
            pros::Rotation new_adiin(_port);
            this->rot.clear();
            this->rot.push_back(new_adiin);
        }


        pros::Rotation get_adiin() {return rot.front();}
};