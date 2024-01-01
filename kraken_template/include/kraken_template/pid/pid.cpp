#pragma once
#include "main.h"

class PIDController {
    private:
	double kP, kI, kD;
	double error_prev, error_total, error_change;
	double range, set_point;

    public:
	PIDController(double kP = 0, double kI = 0, double kD = 0) {
		this->kP = kP;
		this->kI = kI;
		this->kP = kP;
	}

    double calculate(double current_value) {
        double error = current_value - set_point;
	    error_change = error - error_prev;
	    error_total += error;
	    error_prev = error;
	    return (error * kP + error_total * kI + error_change * kD);
    }

    void set_goal(double set_point, double range) {
        this->set_point = set_point;
        this->range = range;
    }

    bool goal_met() {
	    if (fabs(error_prev) < range) {
		    return true;
	    }
	    return false;
    }

    void reset() {
        this->error_prev = 0;
        this->error_total = 0;
        this->error_change = 0;
    }
};