#include "main.h"
#include "_config.cpp"
#include <tuple>



class OPC {
    public:

    void _drivetrain() {
        if (drivetrain.added_drivetrain_motors && devices.controller.get_data_drive_keybinds_set()) {
            int c_master_anaX = devices.controller.master().get_analog(devices.controller.get_ana_x()); 
            int c_master_anaY = devices.controller.master().get_analog(devices.controller.get_ana_y());

            // check and set sens
            double x_sens = 1, y_sens = 1;
            if (devices.controller.get_data_drive_sens_set()) {
                x_sens = devices.controller.get_x_sensitivity();
                y_sens = devices.controller.get_y_sensitivity();
            }

            // check and set reverse
            int rev = 1;
            if (devices.controller.get_data_reverse_drive_direction()) {
                rev = -1;
            }

            drivetrain.left_motors.move((c_master_anaY*y_sens*-c_master_anaX*x_sens));
            drivetrain.right_motors.move((c_master_anaY*y_sens+c_master_anaX*x_sens));

        }
    }

    void _motor() {}

    void _adi() {}
};
OPC opc;