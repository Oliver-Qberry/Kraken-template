#pragma once
#include "main.h"
#include <string>
#include <unordered_map>


class _DISTANCE {
    private:

    public:
        bool added_ditance = false;

        void _new(std::string name, int _port) {
            this->added_ditance = true;
            pros::Distance new_dis(_port);

        }
};