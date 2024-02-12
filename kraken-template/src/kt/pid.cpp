#include "kt/pid.hpp"
#include <math.h>

double kt::util::PIDController::calculate(double current_value) {
        double error = goal - current_value;
	    error_change = error - error_prev;
	    error_total += error;
	    error_prev = error;
	    return (error * kP + error_total * kI + error_change * kD);
}
bool kt::util::PIDController::goal_met() {
	    if (fabs(error_prev) < range || bypass) {
		    return true;
	    }
	    return false;
}