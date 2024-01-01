#include "kraken_template/DRIVETRAIN/DRIVE_MOTORS.cpp"

void reset_drive_positions(_DRIVE_MOTORS left, _DRIVE_MOTORS right) {
    left.set_pos(0.0);
    right.set_pos(0.0);
}

double average_drive_positions(_DRIVE_MOTORS left, _DRIVE_MOTORS right) {
    return (left.get_pos() + right.get_pos())/2;
}