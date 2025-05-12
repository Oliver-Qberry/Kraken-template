#pragma once

#include "kt/devices/optical/optical_node.hpp"
#include "pros/optical.hpp"

#include <string>
#include <unordered_map>
namespace kt
{
    // class for handling rotation sensor
    class Optical
    {
    private:
        // rotation sensor node map
        std::unordered_map<std::string, optical_node> node_map;

    public:
        // adds a new optical node to the handler.
        /*
        parameters:
            name.
            port.
        */
        void new_optical(std::string name, int port);

        // gets the rotation sensor by its name
        pros::Optical get_optical(std::string name);
    };
}