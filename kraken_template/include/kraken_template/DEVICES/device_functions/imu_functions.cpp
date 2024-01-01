#pragma once
#include "main.h"

double imuErrorCalc(double current, double target) {
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