#pragma once

#include "kt/util.hpp"
#include "pros/adi.h"
#include "pros/rotation.hpp"

#include <string>
#include <vector>

class rotation_node {
    public:
    std::string _name;
    std::vector<pros::Rotation> rotation;
};