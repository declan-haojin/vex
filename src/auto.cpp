#include "base.h"
#include "auto.h"
#include <algorithm>

int sign(double x)
{
  if(x > 0) return 1;
  if(x < 0) return -1;
  return 0;
}

void chassis_run(double dist, double k, double turnDeg)
{
  double gyro_kp = 0.7;
  double gyro_kd = 0.5;

  double move_kp = 0.15;
  double move_kd = 0;

  double currentDist = 0;
  double diffTurn;
  double diffDist;
  double turnPower;
  double movePower;
  double gyroLastError;
  double moveLastError;
  
  double moveError = fabs(dist) - fabs(currentDist);
  double gyroError = turnDeg - currentTurn;

  chassis_reset();
  
  gyroLastError = gyroError;
  moveLastError = moveError;

  while(true)
  {
    currentDist = (LF_DEG + LB_DEG + RF_DEG + RB_DEG) * 0.25;
    
    moveError = fabs(dist) - fabs(currentDist);
    gyroError = turnDeg - currentTurn;

    diffDist = moveError - moveLastError;
    diffTurn = gyroError - gyroLastError;

    moveLastError = moveError;
    gyroLastError = gyroError;

    movePower = (move_kp*moveError + move_kd*diffDist) * k;
    turnPower = (gyro_kp*gyroError + gyro_kd*diffTurn) * k;

    if(moveError < 7 && fabs(diffDist) < 0.1) break;

    if(dist > 0)
    {
      if(currentDist > 0.1*fabs(dist)) //查的距离还比较远
      {
        chassis(movePower + turnPower, movePower - turnPower);
      }
      else
      {
        chassis(movePower * 0.7 + turnPower, movePower * 0.7 - turnPower);
      }
    }
    else
    {
      if(currentDist > 0.1*fabs(dist)) //查的距离还比较远
      {
        chassis(-movePower + turnPower, -movePower - turnPower);
      }
      else
      {
        chassis(-movePower * 0.7 + turnPower, -movePower * 0.7 - turnPower);
      }
    }
    wait(1, msec);
  }
  chassis(0, 0);
}

void chassis_turn(double target)
{
  double kp = 0.7;
  double ki = 0;
  double kd = 0.5;

  int timeUsed = 0;

  double iRange = 1.0;
  double iStart = 60;
  double distTorl = 0.1;
  double errorTorl = 1;
  double lim = 100;
  double error = target - currentTurn; // 337-1.78
  double lastError;
  double diffError = 0;
  double i = 0;

  bool isFinished;
  double timeTorl = fabs(error) < 20 ? 700 : fabs(error) * 27;
  double movePower;

  lastError = error;
  isFinished = (error == 0);

  while(!isFinished)
  {
    timeUsed += 10;
    error = target - currentTurn;

    diffError = error - lastError;
    lastError = error;

    if((fabs(error) < errorTorl && fabs(diffError) <= distTorl) || timeUsed > timeTorl) isFinished = true;
    if(fabs(i) < iRange && fabs(error) < iStart)
    {
      i += sign(error) * 0.01;
    }
    if(error * lastError <= 0)
    {
      i = 0;
    }

    movePower = kp * error + kd * diffError + ki * i;
    movePower = fabs(movePower) > lim ? sign(movePower) * lim : movePower;

    chassis(movePower, -movePower);

    wait(10, msec);
  }
  chassis(0, 0);
}

void s()
{
  while(true){if(controller1.ButtonA.pressing()) break;}
}

void red_far()
{
  double t = Brain.timer(sec);
  grab_out(100);
  arm_up(100);
  wt(1.5);
  grab_in(100);
  wt(0.27);
  while(AR_DEG > 50) arm_down(100);

  // s();


  chassis_reset();
  
  while(fabs(LF_DEG)+fabs(LB_DEG)+fabs(RF_DEG)+fabs(RB_DEG) < 4*1200){chassis(30, 30);}
  chassis(0, 0);

  // s();
  // chassis_run(1300, 1.5, 1);

  // s();
  wt(0.27);
  chassis_turn(155);

  wt(0.27);

  // s();

  chassis_run(1100, 1, 155);

  // motorLG.resetRotation();
  // while(fabs(motorLG.rotation(deg)) < 50){grab_out(50);}
  grab_locked();


  // s();

  lift_auto();

  controller1.Screen.clearScreen();
  controller1.Screen.setCursor(1, 1);
  controller1.Screen.print("total time: %3f", Brain.timer(sec) - t);
}

void blue_far()
{
  double t = Brain.timer(sec);
  grab_out(100);
  arm_up(100);
  wt(1.5);
  grab_in(100);
  wt(0.27);
  while(AR_DEG > 50) arm_down(100);

  chassis_reset();
  
  while(fabs(LF_DEG)+fabs(LB_DEG)+fabs(RF_DEG)+fabs(RB_DEG) < 4*1200){chassis(30, 30);}
  chassis(0, 0);

  // s();
  // chassis_run(1300, 1.5, 1);

  // s();
  wt(0.47);
  chassis_turn(-150);

  wt(0.47);

  // s();

  chassis_run(1000, 1, -150);

  // motorLG.resetRotation();
  // while(fabs(motorLG.rotation(deg)) < 50){grab_out(50);}
  grab_locked();


  // s();

  lift_auto();

  controller1.Screen.clearScreen();
  controller1.Screen.setCursor(1, 1);
  controller1.Screen.print("total time: %3f", Brain.timer(sec) - t);
}