#pragma once

#include "kt/auton_handler/auton_node.hpp"
#include "kt/util.hpp"
#include <string>
#include <vector>

namespace kt
{
    // class used to handle auton functions
    class AUTONS
    {

    private:
        // int to handler moving through autons
        int auto_select = 0;
        // select type int
        int auto_select_type;
        // controller keybind used to change autons
        pros::controller_digital_e_t controller_keybind;

    public:
        // constructor for controller keybind
        AUTONS(pros::controller_digital_e_t controller_keybind)
        {
            this->auto_select_type = 0;
            this->controller_keybind = controller_keybind;
        }

        // saved int to count autons saved
        int number_of_autos_saved = 0;
        // vector to store auton nodes
        std::vector<auton_node> auton_node_vector;

        bool editing = false;

        /* function to add an auton to the handler class. parameters:
            the auton functions name.
            the auton functions description.
            the auton function.
        */
        void add_auton(std::string name, std::string description, void (*function)());

        // move to the next auton node in the auton node vector during auton select
        void increment();

        void set_editing(bool edit);

        // gets the current autons name
        std::string current_name();

        // gets the current autons description
        std::string current_desc();

        // runs the current auton
        void run_current_auton();

        // (TASK function) used to select auton during pre match
        void auton_select_task();
        bool is_editing();

    }; // end of AUTONS class
} // end of kt namespace