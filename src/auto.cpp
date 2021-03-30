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
  double gyro_kd = 2;

  double move_kp = 0.37;
  double move_kd = 3.5;

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

    if(moveError < 3 && fabs(diffDist) < 0.1) break;

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
  double kp = 0.6;
  double ki = 1;//30;
  double kd = 2;//20;

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

void chassis_arc(double dist1, double dist2, double movePower)
{
  // double move_kp = 0.49;
  // double move_kd = 3.5;

  // double currentDist1 = 0;
  // double diffDist1;
  // double movePower1;
  // double moveLastError1;

  // double currentDist2 = 0;
  // double diffDist2;
  // double movePower2;
  // double moveLastError2;
  
  // double moveError1 = fabs(dist1) - fabs(currentDist1);
  // double moveError2 = fabs(dist2) - fabs(currentDist2);

  // chassis_reset();
  
  // moveLastError1 = moveError1;
  // moveLastError2 = moveError2;

  // while(true)
  // {
  //   currentDist1 = (LF_DEG + LB_DEG) * 0.5;
  //   currentDist2 = (RF_DEG + RB_DEG) * 0.5;
    
  //   moveError1 = fabs(dist1) - fabs(currentDist1);
  //   moveError2 = fabs(dist2) - fabs(currentDist2);

  //   diffDist1 = moveError1 - moveLastError1;
  //   diffDist2 = moveError2 - moveLastError2;

  //   moveLastError1 = moveError1;
  //   moveLastError2 = moveError2;

  //   movePower1 = move_kp*moveError1 + move_kd*diffDist1;
  //   movePower2 = move_kp*moveError2 + move_kd*diffDist2;

  //   if(moveError1 < 3 && fabs(diffDist1) < 0.1) break;

  //   if(dist1 > 0)
  //   {
  //     if(currentDist1 > 0.1*fabs(dist1)) //查的距离还比较远
  //     {
  //       chassis(movePower, );
  //     }
  //     else
  //     {
  //       chassis((movePower * 0.7 + turnPower)*0.7, movePower * 0.7 - turnPower);
  //     }
  //   }
  //   else
  //   {
  //     if(currentDist > 0.1*fabs(dist)) //查的距离还比较远
  //     {
  //       chassis((-movePower + turnPower)*0.7, -movePower - turnPower);
  //     }
  //     else
  //     {
  //       chassis((-movePower * 0.7 + turnPower)*0.7, -movePower * 0.7 - turnPower);
  //     }
  //   }
  //   wait(1, msec);
  // }
  // chassis(0, 0);
}


void chassis_run1(double dist, double k, double turnDeg, double trig)
{
  double gyro_kp = 0.7;
  double gyro_kd = 2;

  double move_kp = 0.37;
  double move_kd = 3.5;

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

    if(currentDist > trig) grab_in(100); 
    
    moveError = fabs(dist) - fabs(currentDist);
    gyroError = turnDeg - currentTurn;

    diffDist = moveError - moveLastError;
    diffTurn = gyroError - gyroLastError;

    moveLastError = moveError;
    gyroLastError = gyroError;

    movePower = (move_kp*moveError + move_kd*diffDist) * k;
    turnPower = (gyro_kp*gyroError + gyro_kd*diffTurn) * k;

    if(moveError < 3 && fabs(diffDist) < 0.1) break;

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


void arm_auto_up(double x)
{
  // grab_locked();
  grab_in(50.7);
  while(AR_DEG < x) arm_up(77.7), lift_up(100);
  arm_locked();
  wt(0.97);
  lift_locked();
}

void red_far()
{
  // grab_in(97.7);
  // chassis_run(797, 27.7, 0);

  imu_reset();
  chassis_turn(-30);  
  chassis_arc(-977, 57.7, 0);

  // chassis_run(-1000, 57.7, 0);
}

int lift_up1_callback()
{
  while(fabs(LT_DEG) < 387)
  {
    lift_up(100);
  }
  lift_locked();
  return 0;
}

inline void s(){
  while(true){
    if(controller1.ButtonA.pressing()){
      break;
    }
  }
}

void red_close()
{
  lift_reset();
  imu_reset();
  arm_locked();


  // s();
  grab_in(25);

  // task lift_up1 = task(lift_up1_callback);
  chassis_run(900, 0.7, 0);
  grab_in(100);
  // lift_up1.stop();
  wt(0.27);
  // s();
  chassis_turn(-135);

  // return;
  // grab_locked();
  
  // return;

  wt(0.27);
  // s();
  chassis_run(900, 0.5, -134.6);

  wt(0.27);
  // s();


  motorLG.resetRotation();
  while(fabs(motorLG.rotation(deg)) < 100){grab_out(50);}
  grab_locked();

  wt(0.1);

  grab_in(10);
  while(LIFT_MAX - LT_DEG > 3.7)
  {
    if(fabs(LT_DEG) > LIFT_MAX*6/7) lift_up(20);
    else if(fabs(LT_DEG) > LIFT_MAX*5/7) lift_up(40);
    else lift_up(100);
  }
  lift_locked();
  grab_locked();
  wt(0.5);

  chassis(-37, -37);
  wt(1);
  chassis(0, 0);

  while(1)
  {
    controller1.Screen.clearScreen();
    controller1.Screen.setCursor(1, 1);
    controller1.Screen.print("imu: %5f", imu.rotation());
  }
}