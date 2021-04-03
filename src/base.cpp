#include "base.h"

void m(motor motorName, double speed, double torq)
{
  motorName.setMaxTorque(torq, pct);
  motorName.spin(fwd, speed, pct);
}
void m_group(motor_group motorGroup, double speed, double torq)
{
  motorGroup.setMaxTorque(torq, pct);
  motorGroup.spin(fwd, speed, pct);
}
void set_brake_mood(motor motorName, bool isBrake)
{
  if(isBrake) motorName.setBrake(brake);
  else motorName.setBrake(coast);
}

void chassis(double left, double right)
{
  m_group(chassisLeft, left);
  m_group(chassisRight, right);
}

void set_chassis_brake_mood(bool x)
{
  if(x) //BRAKE
  {
    chassisLeft.setStopping(brake);
    chassisRight.setStopping(brake);
  }
  else 
  {
    chassisLeft.setStopping(coast);
    chassisRight.setStopping(coast);
  }
}
void chassis_reset()
{
  chassisLeft.resetRotation();
  chassisRight.resetRotation();
}

void shift(double front, double back)
{
  m(motorLF, front);
  m(motorLB, back);
  m(motorRF, back);
  m(motorRB, front);
}

void grab_in(double speed)
{
  m_group(grab, speed);
}
void grab_out(double speed)
{
  m_group(grab, -speed);
}
void grab_locked()
{
  m_group(grab, 1, 0);
}


void lift(double speed)
{
  m(motorLT, speed);
}
void lift_up(double speed)
{
  m(motorLT, speed);
}
void lift_down(double speed)
{
  m(motorLT, -speed);
}
void lift_locked()
{
  m(motorLT, 1, 0);
}
void lift_auto()//1777
{
  grab_in(10);
  while(LIFT_MAX - LT_DEG > 3.7)
  {
    if(LT_DEG > LIFT_MAX*5/7) lift_up(20);
    else if(fabs(LT_DEG) > LIFT_MAX*3/7) lift_up(50);
    else lift_up(100);
  }
  lift_locked();
  grab_locked();
  chassis(-37, -37);
  wait(2, sec);
  chassis(0, 0);
}
void lift_reset()
{
  m(motorLT, -100, 1);
  wait(3, sec);
  m(motorLT, 20, 90);
  wait(1, sec);
  lift_locked();
  motorLT.resetRotation();
}

void arm_up(double speed)
{
  m(motorAR, speed);
}
void arm_down(double speed)
{
  m(motorAR, -speed);
}
void arm_locked()
{
  m(motorAR, 10, 0);
}


void imu_reset()
{
  imu.calibrate();
  while (imu.isCalibrating()){}
}
          