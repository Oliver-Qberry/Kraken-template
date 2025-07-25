#include "kt/auton_handler/auton_editor.hpp"
#include "auton.hpp"
#include "config.hpp"
#include "kt/util.hpp"

// interpreter
void kt::auton_editor::runDriverAuton()
{
    for (const auto &cmd : driverAuton)
    {
        switch (cmd.type)
        {
        case kt::CommandType::SetDrivePID:
            chassis.drive_pid_constants(std::stod(cmd.param1), std::stod(cmd.param2), std::stod(cmd.param3), std::stod(cmd.param4));
            break;
        case kt::CommandType::SetTurnPID:
            chassis.drive_pid_constants(std::stod(cmd.param1), std::stod(cmd.param2), std::stod(cmd.param3), std::stod(cmd.param4));
            break;
        case kt::CommandType::Move:
            if (cmd.param2 == "" /*|| cmd.param2 == null*/) // 1 parameter call
            {
                chassis.move(std::stoi(cmd.param1));
            }
            else if (cmd.param3 == "") // 2 paramter call
            {
                chassis.move(std::stoi(cmd.param1), std::stoi(cmd.param2));
            }
            else
            {
                chassis.move(std::stod(cmd.param1), std::stod(cmd.param2), std::stod(cmd.param3));
            }
            break;
        case kt::CommandType::Turn:
            if (cmd.param2 == "")
            {
                chassis.turn(std::stoi(cmd.param1));
            }
            else
            {
                chassis.turn(std::stoi(cmd.param1), std::stoi(cmd.param2));
            }
            break;
        case kt::CommandType::Delay:
            pros::delay(std::stoi(cmd.param1));
            break;
            // Add the rest
        case kt::CommandType::MoveMotor:
            motor.get_motor(cmd.param1).move(std::stoi(cmd.param2));
            break;
        case kt::CommandType::Brake:
            motor.get_motor(cmd.param1).brake();
            break;
        case kt::CommandType::Pneumatic:
            bool value = (cmd.param2 == "false") ? false : true;
            AdiDigitalOut.get_adi(cmd.param1).set_value(value);
            break;
        }
    }
}

void kt::auton_editor::set_level(int level)
{
    switch (level)
    {
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    }
}

void kt::auton_editor::reset()
{
    // FIXME: make the vector empty
    // driverAuton = NULL;
}