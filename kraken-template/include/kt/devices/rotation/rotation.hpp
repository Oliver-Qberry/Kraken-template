#pragma once

#include "kt/devices/rotation/rotation_node.hpp"
#include "pros/rotation.hpp"

#include <string>
#include <unordered_map>

namespace kt {
// class for handling rotation sensor
class Rotation {
    private:
    // rotation sensor node map
    std::unordered_map<std::string, rotation_node> node_map;

    public:
    // adds a new rotation node to the handler.
    /*
    parameters:
        name.
        port.
    */
    void new_rotation(std::string name, int port);

    //gets the rotation sensor by its name
    pros::Rotation get_rotation(std::string name);
};
}