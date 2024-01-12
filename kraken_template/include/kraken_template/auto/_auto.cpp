//#pragma once
#include "main.h"

#include "_auto_node.cpp"

#include <string>
#include <unordered_map>
#include <vector>

class _AUTO {
    private:
        std::string default_auto_name;
        std::vector<std::string> node_names;
        std::unordered_map<std::string, auto_node> node_map;
    public:

        void new_auto(std::string name, std::string desc, int function) {
            this->node_map[name] = auto_node(function, desc);
        }

        void set_default_auto(std::string name) {
            this->default_auto_name = name;
        }

        void run_auto(std::string name) {
            this->node_map[name].run();
        }
};