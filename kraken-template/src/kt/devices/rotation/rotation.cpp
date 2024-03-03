#include "kt/devices/rotation/rotation.hpp"

void kt::Rotation::new_rotation(std::string name, int port) {
    pros::Rotation new_rot(port);
    node_map[name].rotation.clear();
    node_map[name].rotation.push_back(new_rot);
}

pros::Rotation kt::Rotation::get_rotation(std::string name) {
    return node_map[name].rotation.front();
}