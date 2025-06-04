#include "kt/auton_handler/auton_handler.hpp"

void kt::AUTONS::add_auton(std::string name, std::string description, void (*function)())
{
    auton_node node(name, description, function);
    this->auton_node_vector.push_back(node);
    this->number_of_autos_saved += 1;
}

void kt::AUTONS::increment()
{
    auto_select += 1;
    if (auto_select >= auton_node_vector.size())
    {
        auto_select = 0;
    }
}

std::string kt::AUTONS::current_name() { return auton_node_vector[auto_select]._name; }

std::string kt::AUTONS::current_desc() { return auton_node_vector[auto_select]._desc; }

void kt::AUTONS::run_current_auton() { auton_node_vector[auto_select].run(); }

void kt::AUTONS::auton_select_task()
{
    if (auto_select_type == 0)
    {
        // controller
        if (master.get_digital_new_press(controller_keybind))
        {
            increment();
        }
    }
}

void kt::AUTONS::set_editing(bool edit)
{
    this->editing = edit;
}
bool kt::AUTONS::is_editing()
{
    return editing;
}