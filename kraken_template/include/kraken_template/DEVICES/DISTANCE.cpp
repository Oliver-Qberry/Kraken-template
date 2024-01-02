#pragma once
#include "main.h"

#include "nodes/DISTANCE_Node.cpp"


class _DISTANCE {
    private:
        std::vector<std::string> node_names;
        std::unordered_map<std::string, Node_DISTANCE> node_map;

    public:
        bool added_distance = false;

        void new_distance(std::string name, int port) {
            Node_DISTANCE node(name, port);
            this->node_names.push_back(name);
            this->node_map[name] = node;
            this->added_distance = true;
        }

        pros::Distance get_distance(std::string name) {
            return node_map[name].get_distance();
        }

        std::vector<std::string> get_distance_names() {
            return node_names;
        }

        Node_DISTANCE get_distance_node(std::string name) {
            return node_map[name];
        }
};