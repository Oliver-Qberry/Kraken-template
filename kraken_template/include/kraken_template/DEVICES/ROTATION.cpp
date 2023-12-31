#pragma once
#include "main.h"



class _ROTATION {
    private:
        std::vector<std::string> rotation_names;
        std::vector<pros::Rotation> rotation_rotation;

    public:
        bool added_rotation = false;

        void _new(std::string name, int _port) {
            this->added_rotation = true;
            pros::Rotation new_rot(_port);
            this->rotation_rotation.push_back(new_rot);
            this->rotation_names.push_back(name);
        }

        std::vector<std::string> get_distance_data_names() {return this->rotation_names;}

        pros::Rotation distance(std::string name) {
            if (this->added_rotation) {
                auto it = std::find(this->rotation_names.begin(), this->rotation_names.end(), name);
                if (it != this->rotation_names.end()) {
                    auto idx = std::distance(this->rotation_names.begin(), it);
                    return this->rotation_rotation[idx];
                }
            }
            pros::Rotation n(0);
            return n;
        }
};