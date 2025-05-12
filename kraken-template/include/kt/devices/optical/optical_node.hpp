#pragma once

#include "kt/util.hpp"
#include "pros/adi.h"
#include "pros/optical.hpp"

#include <string>
#include <vector>

// rotation sensor node
class optical_node
{
public:
    // nodes name
    std::string _name;
    // nodes optical sensor
    std::vector<pros::Optical> optical;
};