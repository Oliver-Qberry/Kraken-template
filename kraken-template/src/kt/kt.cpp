#include "kt/kt.hpp"
#include "pros/rtos.hpp"
#include "user/devices.hpp"
#include "user/auton.hpp"

using namespace kt::devices;
using namespace pros;

namespace kt
{

    void init()
    {
        // ========== Start framework tasks ==========
        // pros::Task task_odometry(update_position_task);
        Task task_auton(auton_select_task);
        Task task_lcd(print_to_lcd_task);

        initialize_devices();

        chassis_setup();

        // (add other global framework init here if needed)
    }

} // namespace kt
