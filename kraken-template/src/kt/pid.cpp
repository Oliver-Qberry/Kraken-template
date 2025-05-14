#include "kt/pid.hpp"
#include <math.h>

double kt::util::PIDController::calculate(double current_value)
{
	// calculate pid errors
	double error = goal - current_value; // in v3_3 its current-desired
	error_change = error - error_prev;
	error_total += error;
	error_prev = error;
	// return the sum * const
	return (error * kP + error_total * kI + error_change * kD);
}

bool kt::util::PIDController::goal_met()
{
	// if the prev error is within the range
	// or if bypass is true
	if (fabs(error_prev) < range || bypass)
	{
		return true;
	}
	// else return false
	return false;
}