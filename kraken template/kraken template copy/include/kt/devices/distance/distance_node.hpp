#pragma once

#include "pros/distance.hpp"

#include <string>
#include <vector>

class distance_node {
    public:
    std::string _name;
    std::vector<pros::Distance> distance;
};