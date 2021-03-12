#include "vex.h"

#define currentTurn   inert.rotation(deg)
#define wt(x)         wait(x, sec)

int sign(double x);

void chassis_run(double dist, double pw, double turnDeg);
void chassis_turn(double target);