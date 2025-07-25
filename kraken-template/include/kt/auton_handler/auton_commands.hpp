#pragma once

#include <string>

namespace kt
{
    enum class CommandType
    {
        SetDrivePID, // 4 params - doubles
        SetTurnPID,  // 4 params - doubles
        Move,        // 1, 2, or 3 params  - ints or 3 doubles
        Turn,        // 1, or 2 params - ints
        MoveTo,      // 2 params - Point and a double
        Delay,       // 1 params - int
        MoveMotor,   // 2 params - string and int
        Brake,       // 1 params - string
        Pneumatic,   // 2 params - string and bool
    };

    struct Command
    {
        CommandType type;
        std::string param1 = "";
        std::string param2 = "";
        std::string param3 = "";
        std::string param4 = "";
    };
    struct EditorScreen
    {
        std::string line1 = "";
        std::string line2 = "";
        std::string line3 = "";
    };
}
