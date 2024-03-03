#pragma once

#include "kt/util.hpp"
#include "pros/adi.h"
#include "pros/rotation.hpp"

#include <string>
#include <vector>

// rotation sensor node
class rotation_node {
    public:
    // nodes name
    std::string _name;
    // nodes rotation sensor
    std::vector<pros::Rotation> rotation;
};