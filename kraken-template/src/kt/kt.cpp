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
        initialize_devices();

        chassis_setup();
        if (chassis.get_odometry_status())
        {
            Task task_odometry([]()
                               {
                                   while (true)
                                   {
                                       chassis.update_odometry();
                                       pros::delay(kt::util::DELAY_TIME);
                                   }
                               });
        }
        // ========== Start framework tasks ==========
        Task task_auton(auton_select_task);
        Task task_lcd(print_to_lcd_task);

        // (add other global framework init here if needed)
    }

} // namespace kt
