#include "vex.h"

#define currentTurn   imu.rotation(deg)
#define wt(x)         wait(x, sec)

int sign(double x);

void chassis_run(double dist, double k, double turnDeg);
void chassis_run1(double dist, double k, double turnDeg, double trig);
void chassis_turn(double target);
void chassis_arc();

void blue_far();
void blue_close();
void red_far();
void red_close();