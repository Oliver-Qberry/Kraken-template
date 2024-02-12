#pragma once

#include "kt/devices/rotation/rotation_node.hpp"
#include "pros/rotation.hpp"
#include <string>
#include <unordered_map>

namespace kt {
class Rotation {
    private:
    std::unordered_map<std::string, rotation_node> node_map;
    public:

    void new_rotation(std::string name, int port) {
        pros::Rotation new_rot(port);
        node_map[name].rotation.clear();
        node_map[name].rotation.push_back(new_rot);
    }

    pros::Rotation get_rotation(std::string name) {
        return node_map[name].rotation.front();
    }
};
}