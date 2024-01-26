#pragma once
#include "main.h"

#include "nodes/ROTATION_Node.cpp"
#include <string>
#include <unordered_map>



class _ROTATION {
    private:
        std::vector<std::string> node_names;
        std::unordered_map<std::string, Node_ROTATION> node_map;

    public:
        bool added_rotation = false;

        void new_rotation(std::string name, int port) {
            this->node_names.push_back(name);
            Node_ROTATION node(name, port);
            this->node_map[name] = node;
            this->added_rotation = true;
        }



        pros::Rotation get_rotation(std::string name) {
            return node_map[name].get_rotation();
        }

        std::vector<std::string> get_rotation_names() {
            return node_names;
        }

        Node_ROTATION get_rotation_node(std::string name) {
            return node_map[name];
        }
};