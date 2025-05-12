#pragma once

#include "kt/devices/vision/vision_node.hpp"
#include "pros/vision.hpp"

#include <string>
#include <unordered_map>

namespace kt
{
    // class for handling vision sensor
    class Vision
    {
    private:
        // vision sensor node map
        std::unordered_map<std::string, vision_node> node_map;

    public:
        // adds a new rotation node to the handler.
        /*
        parameters:
            name.
            port.
        */
        void new_vision(std::string name, int port);

        // gets the vision sensor by its name
        pros::Vision get_vision(std::string name);
    };
}