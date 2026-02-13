#pragma once

namespace kt
{
    namespace util
    {

        // general pid controller class
        class PIDController
        {
        public:
            // pid constants
            double kP, kI, kD;
            // pid errors
            double error_prev, error_total, error_change;
            double max_integral = 100.0;
            //
            double range, goal;
            // bypass pid goal met
            bool bypass = false;

            // settling time variables
            int settling_time = 100;
            int settled_time = 0;

            // sets the P I D constants
            void set_pid_constants(double kP, double kI, double kD)
            {
                this->kP = kP;
                this->kI = kI;
                this->kD = kD;
            }

            // sets the pids end goal value
            void set_goal(double goal)
            {
                this->goal = goal;
            }

            // sets the pid end goal value and the pid exit range
            void set_goal(double goal, double range)
            {
                this->goal = goal;
                this->range = range;
            }

            // sets the pid exit range
            void set_range(double range, double exit_time = 20)
            {
                this->range = range;
                this->settling_time = exit_time;
            }

            // resets the pid errors
            void reset()
            {
                this->error_prev = 0;
                this->error_total = 0;
                this->error_change = 0;
                this->settled_time = 0;
            }
            void increase_settled_time(int time);

            // calculate pid with current value. returns the pids output as a double.
            double calculate(double current_value);
            // calculate turn pid with current value. returns the pids output as a double.
            double calculate_turn(double current_error);
            // check if the goal has been met (prev_error within the exit range). returns a bool.
            bool goal_met();
        };

    } // end of util namespace
} // end of kt namespace