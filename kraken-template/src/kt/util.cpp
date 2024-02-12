#include "main.h"



pros::Controller master(pros::E_CONTROLLER_MASTER);


namespace kt {
namespace util {

bool reversed_active(double input) {
  if (input < 0) return true;
  return false;
}

int sgn(double input) {
  if (input > 0)
    return 1;
  else if (input < 0)
    return -1;
  return 0;
}

double imu_error_calc(double current, double target) {
    double E1=target-current, E2=-1*(current-(target-360)), E3=target-(current-360), Efinal;
    if (fabs(E1) < fabs(E2) && fabs(E1) < fabs(E3)) {
      Efinal = E1;
    } 
    if (fabs(E2) < fabs(E1) && fabs(E2) < fabs(E3)) {
      Efinal = E2;
    } 
    if (fabs(E3) < fabs(E1) && fabs(E3) < fabs(E2)) {
      Efinal = E3;
    }
    return Efinal;
}

}
}