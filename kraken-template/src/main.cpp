/*
Kraken Template by Cole Johnson of 2605E
In collaboration with 2605A

template is made for SHS VRC teams and is based off of what we have at SHS and need for the VRC robot
*/
// includes the pros and kt api
#include "main.h"
// includes the framework
#include "kt/kt.hpp"
// includes the config file for device setup
#include "user/devices.hpp"
// includes the auton file for auton setup
#include "user/auton.hpp"
// includes the driver file for driver setup
#include "user/driver.hpp"
// other includes

/*
a few different namespaces are adding for your convenience.
HOWEVER remember that there is some crossover between kt and pros so you may still have to use them in some cases.
*/
using namespace std;
using namespace pros;
using namespace v5;
using namespace kt::driver;
using namespace kt::devices;

// ==================== initialize ==================== //
/*
the initialize function is run when the program is started.

all other competition modes are blocked by initialize so it is recommended
to keep execution time for this mode under a few seconds.
*/
void initialize()
{
    // Register autons before any framework tasks may read from the auton list.
    initialize_auton();

    // init framework (background tasks, devices etc.)
    kt::init();

    // ========== other initialize functions ========== //
    // chassis initialize -> chassis
    kt::devices::chassis.initialize();

} // end of initialize function

// ==================== competition initialize ==================== //
/*
runs after initialize(), and before autonomous when connected to the field
management system or the vex competition switch.

this task will exit when the robot is enabled and autonomous or opcontrol starts.

this is not used in the base kraken template but feel free to add to it.
*/
void competition_initialize() {}

// ==================== disabled ==================== //
/*
runs while the robot is in the disabled state of field management system or
the vex competition switch, following either autonomous or opcontrol. when
the robot is enabled, this task will exit.

this is not used in the base kraken template but feel free to add to it.
*/
void disabled() {}

// ==================== operator control ==================== //
/*
runs the operator control code. this function will be started whenever the robot is enabled via
the field management system or the vex competition switch in the operator control mode.

if no competition control is connected, this function will run immediately following initialize().

if the robot is disabled or communications is lost, the operator control task will be stopped.
re-enabling the robot will restart the task, not resume it from where it left off.
*/
void opcontrol()
{
    user_driver(); // Runs driver code from user/

} // end of opcontrol function

// ==================== autonomous ==================== //
/*
runs the user autonomous code. This function will be started whenever the robot is enabled via
the field management system or the vex competition switch in the autonomous mode.

if the robot is disabled or communications is lost, the autonomous task
will be stopped. re-enabling the robot will restart the task, not re-start it
from where it left off.

with the kraken template and autons class, it will run whatever the current auton is during autonomous.
the current auton can be changed by using the auton selector.
*/

void autonomous()
{
    autons.run_current_auton();
}
