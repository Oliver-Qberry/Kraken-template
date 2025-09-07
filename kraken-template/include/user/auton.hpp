#pragma once
// kraken api
#include "kt/api.hpp"
// handler for auton
#include "kt/auton_handler/auton_handler.hpp"

// autons extern def
extern kt::AUTONS autons;

// function to save auto functions to auton class
void initialize_auton();
// task to handle auton selection during pre match
void auton_select_task();