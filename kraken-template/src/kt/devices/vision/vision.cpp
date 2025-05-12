#include "kt/devices/vision/vision.hpp"

void kt::Vision::new_vision(std::string name, int port)
{
    pros::Vision new_vis(port);
    node_map[name].vision.clear();
    node_map[name].vision.push_back(new_vis);
}

pros::Vision kt::Vision::get_vision(std::string name)
{
    return node_map[name].vision.front();
}