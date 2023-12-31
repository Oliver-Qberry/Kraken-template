#pragma once
#include "main.h"

#include "DEVICES/_DEVICES.cpp"
DEVICES devices;

#include "DRIVETRAIN/_DRIVETRAIN.cpp"
_DRIVETRAIN drivetrain;

// opc not included in config as config is referenced in op
// cannot define inside its base file