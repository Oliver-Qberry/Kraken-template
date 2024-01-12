#include "main.h"

class Node_CONTROLLER_DATA {
    public:
        bool _drive_keybinds_set = false;
        bool _drive_sens_set = false;
        pros::controller_analog_e_t _controller_analog_x_id;
        pros::controller_analog_e_t _controller_analog_y_id;
        bool _reverse_drive_direction;

        double _x_sensitivity;
        double _y_sensitivity;

        void set_drive_data(pros::controller_analog_e_t _controller_analog_x_id,
                            pros::controller_analog_e_t _controller_analog_y_id, bool _reverse_drive_direction) {
            this->_controller_analog_x_id = _controller_analog_x_id;
            this->_controller_analog_y_id = _controller_analog_y_id;
            this->_reverse_drive_direction = _reverse_drive_direction;
            this->_drive_keybinds_set = true;
        }

        void set_sensitivity_data(double _x_sensitivity, double _y_sensitivity) {
            this->_x_sensitivity = _x_sensitivity;
            this->_y_sensitivity = _y_sensitivity;
            this->_drive_sens_set = true;
        }
};