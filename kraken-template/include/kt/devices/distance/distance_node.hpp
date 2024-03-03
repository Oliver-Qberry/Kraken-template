#pragma once

#include "pros/distance.hpp"

#include <string>
#include <vector>

// distance sensor node
class distance_node {
    public:
    // nodes name
    std::string _name;
    // nodes distance sensor
    std::vector<pros::Distance> distance;
};