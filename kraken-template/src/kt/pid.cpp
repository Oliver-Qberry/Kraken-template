#include "kt/pid.hpp"
#include <math.h>

double kt::util::PIDController::calculate(double current_value)
{
	// calculate pid errors
	double error = goal - current_value; // in v3_3 its current-desired
	error_change = error - error_prev;
	error_total += error;
	error_prev = error;

	if (error_total > max_integral)
		error_total = max_integral;
	if (error_total < -max_integral)
		error_total = -max_integral;

	// return the sum * const
	return (error * kP + error_total * kI + error_change * kD);
}

double kt::util::PIDController::calculate_turn(double current_error)
{
	// calculate pid errors
	double error = current_error; // in v3_3 its current-desired
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
	if ((fabs(error_prev) < range && settled_time >= settling_time) || bypass) // TODO: how to access settled time
	{
		return true;
	}
	else if (fabs(error_prev) < range)
	{
		settled_time += 20;
		return false;
	}
	else if (fabs(error_prev) > range)
	{
		settled_time = 0;
	}
	// else return false
	return false;
}

void kt::util::PIDController::increase_settled_time(int time)
{
	settled_time += time;
}