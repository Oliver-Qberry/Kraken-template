// kt includes
#include "auton.hpp"
#include "config.hpp"
#include "kt/util.hpp"

// ==================== add your auto functions here ==================== //
/*
this is were you can write your auto functions.
just make sure to add them to the autons class when your done.
*/

void test1() {
    std::cout<<"test1"<<std::endl;
}
void test2() {
    std::cout<<"test2"<<std::endl;
}
void test3() {
    std::cout<<"test3"<<std::endl;
}

// ==================== save your auto functions here ==================== //
/*
function called in initialize to set up the autons. 
add your auton by typing autons.add_auton("your autons name", "your autons description", your_autons_function);
doing so will add your auton to the auton class which handles the auto select and running the auton function for you.
*/
void initialize_auton() {
    autons.add_auton("test1", "d1", test1);
    autons.add_auton("test2", "d2", test2);
    autons.add_auton("test3", "d3", test3);
}

// ==================== auton select function ==================== //
/*
this is a task function used to check inputs for the auton select function. 
DO NOT CHANGE ANYTHING IN THIS FUNCTION UNLESS YOU KNOW WHAT YOU ARE DOING.
*/
void auton_select_task() {
    while (true) {
        autons.auton_select_task();
        pros::delay(kt::util::DELAY_TIME);
    }
}