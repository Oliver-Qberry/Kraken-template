#pragma once
#include "main.h"
#include <string>
#include <unordered_map>
#include <vector>


class _DISTANCE {
    private:
        std::vector<std::string> distance_names;
        std::vector<pros::Distance> distance_distance;

    public:
        bool added_distance = false;

        void _new(std::string name, int _port) {
            this->added_distance = true;
            pros::Distance new_dis(_port);
            this->distance_distance.push_back(new_dis);
            this->distance_names.push_back(name);
        }

        std::vector<std::string> get_distance_data_names() {return this->distance_names;}

        pros::Distance distance(std::string name) {
            if (this->added_distance) {
                auto it = std::find(this->distance_names.begin(), this->distance_names.end(), name);
                if (it != this->distance_names.end()) {
                    auto idx = std::distance(this->distance_names.begin(), it);
                    return this->distance_distance[idx];
                }
            }
            pros::Distance n(0);
            return n;
        }
};