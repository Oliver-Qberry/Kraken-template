#pragma once

#include "kt/devices/distance/distance_node.hpp"
#include "pros/distance.hpp"

#include <string>
#include <unordered_map>

namespace kt {
// class for handling distance sensors
class Distance {
    private:
    // distance sensor node map
    std::unordered_map<std::string, distance_node> node_map;

    public:
    // function to add a new distance sensor to the handler class
    /*
    parameters:
        name.
        port.
    */
    void new_distance(std::string name, int port);
    
    // get the distance sensor by its name
    pros::Distance get_distance(std::string name);

}; // end of Distance class
} // end of kt namespace