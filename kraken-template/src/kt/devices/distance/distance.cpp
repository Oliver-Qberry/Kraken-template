#include "kt/devices/distance/distance.hpp"

void kt::Distance::new_distance(std::string name, int port) {
    pros::Distance new_dis(port);
    node_map[name].distance.clear();
    node_map[name].distance.push_back(new_dis);
}

pros::Distance kt::Distance::get_distance(std::string name) {
    return node_map[name].distance.front();
}