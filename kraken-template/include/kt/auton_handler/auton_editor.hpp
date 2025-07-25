#pragma once

#include "kt/auton_handler/auton_node.hpp"
#include "kt/util.hpp"
#include <string>
#include <vector>

#include "kt/auton_handler/auton_commands.hpp"

namespace kt
{
    // class used to handle auton functions
    namespace auton_editor
    {
        std::vector<kt::Command> driverAuton;

        EditorScreen editorScreenLines = {
            "> Edit",
            "Run",
            ""};

        void runDriverAuton() {};
        void set_level(int level) {};
        void reset() {};
    };
} // end of kt namespace