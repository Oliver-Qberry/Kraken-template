#pragma once
#include "main.h"
#include <string>
#include <unordered_map>
#include <vector>


class _ADIDigitalIn {
    private:
        std::vector<std::string> adi_names;
        std::unordered_map<std::string, pros::ADIDigitalIn> map_adi;

        std::unordered_map<std::string, bool> map_adi_data_has_adv_data;

        std::unordered_map<std::string, pros::controller_digital_e_t> map_adi_data_keybind;
        std::unordered_map<std::string, bool> map_adi_data_have_reverse_flow;
        std::unordered_map<std::string, bool> map_adi_data_in_toggle_mode;

    public:
        void _new(std::string name, char port) {
            pros::ADIDigitalIn new_adi(port);
            map_adi[name] = new_adi;
            adi_names.push_back(name);
            map_adi_data_has_adv_data[name] = false; 
        }

        void set_keybinds(std::string name, pros::controller_digital_e_t keybind, 
                               bool in_toggle_mode = false, bool reverse_flow = false) {
            map_adi_data_has_adv_data[name] = true;
            map_adi_data_keybind[name] = keybind;
            map_adi_data_in_toggle_mode[name] = in_toggle_mode;
            map_adi_data_have_reverse_flow[name] = reverse_flow;
        }


        pros::ADIDigitalIn ADI(std::string name) {return map_adi[name];}


        std::vector<std::string> get_adid_data_adid_in_names() {
            return adi_names;}
        bool get_adi_has_data(std::string name) {
            return map_adi_data_has_adv_data[name];}
        pros::controller_digital_e_t get_adi_data_keybind(std::string name) {
            return map_adi_data_keybind[name];}
        bool get_adi_data_have_reverse_flow(std::string name) {
            return map_adi_data_have_reverse_flow[name];}
        bool get_adi_data_in_toggle_mode(std::string name) {
            return map_adi_data_in_toggle_mode[name];}
};