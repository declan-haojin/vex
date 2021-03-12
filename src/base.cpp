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
  grab.stop(hold);
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
  motorLT.stop(hold);
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
  motorAR.stop(hold);
}

void inert_reset()
{
  inert.calibrate();
  while (inert.isCalibrating()){}
}
          