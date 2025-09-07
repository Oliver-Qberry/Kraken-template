#pragma once

#include "main.h"
#include "user/devices.hpp"
#include "pros/adi.hpp"
#include "pros/motors.h"
#include "pros/imu.hpp"
#include "kt/kt.hpp"

namespace kt::driver
{
    // is this were we have lcd functions
    void user_driver();
} // namespace kt::driver