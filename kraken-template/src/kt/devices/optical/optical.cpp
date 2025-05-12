#include "kt/devices/optical/optical.hpp"

void kt::Optical::new_optical(std::string name, int port)
{
    pros::Optical new_rot(port);
    node_map[name].optical.clear();
    node_map[name].optical.push_back(new_rot);
}

pros::Optical kt::Optical::get_optical(std::string name)
{
    return node_map[name].optical.front();
}