#pragma once
#include "main.h"
#include <string>
#include <vector>

class Node_DISTANCE {
    public:
        std::string _name;
        std::vector<pros::Distance> dis;
        
        Node_DISTANCE (std::string _name, int _port) {
            this->_name = _name;
            pros::Distance new_dis(_port);
            this->dis.clear();
            this->dis.push_back(new_dis);
        }

        pros::Distance get_distance() {return dis.front();}
};