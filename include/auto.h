#include "vex.h"

#define currentTurn   imu.rotation(deg)
#define wt(x)         wait(x, sec)

int sign(double x);

void chassis_run(double dist, double k, double turnDeg);
void chassis_shift(double dist, double pw, double turnDeg);
void chassis_turn(double target);


void red_far();
void blue_far();