#pragma once

#include "kt/util.hpp"
#include "pros/adi.h"
#include "pros/vision.hpp"

#include <string>
#include <vector>

// rotation sensor node
class vision_node
{
public:
    // nodes name
    std::string _name;
    // nodes vision sensor
    std::vector<pros::Vision> vision;
};