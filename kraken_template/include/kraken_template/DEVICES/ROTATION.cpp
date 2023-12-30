#pragma once
#include "main.h"
#include <string>
#include <unordered_map>


class _ROTATION {
    private:

    public:
        bool added_rotation = false;

        void _new(std::string name, int _port) {
            this->added_rotation = true;
            pros::Rotation new_rot(_port);

        }
};