#pragma once

namespace kt {
namespace util {

class PIDController {
    public:
	double kP, kI, kD;
	double error_prev, error_total, error_change;
	double range, goal;
    bool bypass = false;

    void set_pid_constants(double kP, double kI, double kD) {
		this->kP = kP;
		this->kI = kI;
		this->kP = kP;
    }
    void set_goal(double goal) {
        this->goal = goal;
    }
    void set_goal(double goal, double range) {
        this->goal = goal;
        this->range = range;
    }
    void set_range(double range) {
        this->range = range;
    }
    void reset() {
        this->error_prev = 0;
        this->error_total = 0;
        this->error_change = 0;
    }

    double calculate(double current_value);
    bool goal_met();
};

}
}