#pragma once

#include "kt/devices/distance/distance_node.hpp"
#include "pros/distance.hpp"
#include <string>
#include <unordered_map>

namespace kt {
class Distance {
    
    private:
    std::unordered_map<std::string, distance_node> node_map;
    public:
    
    void new_distance(std::string name, int port) {
        pros::Distance new_dis(port);
        node_map[name].distance.clear();
        node_map[name].distance.push_back(new_dis);
    }
    
    pros::Distance get_distance(std::string name) {
        return node_map[name].distance.front();
    }
};
}