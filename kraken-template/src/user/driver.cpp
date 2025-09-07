#include "driver.hpp"
#include "kt/util.hpp"
#include "pros/rtos.hpp"

using namespace kt::devices;
using namespace pros;

namespace kt::driver
{
    void user_driver()
    {
        // the while loop constantly loops the functions while the taks is active
        while (true)
        {
            // your operator control code should go here

            // this in an example of how you can use the motors build in opcontrol
            // this is the same motor setup in devices.cpp
            motor.opcontrol("motor");

            // this is how you can call the build in opcontrol function for the chassis class
            chassis.opcontrol();

            // a small delay is needed to prevent issuses
            delay(kt::util::DELAY_TIME);
        } // end of while loop
    }
} // namespace kt::driver