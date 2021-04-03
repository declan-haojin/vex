#include "manual.h"
#include "base.h"

void chassis_manual()
{
  double left = SENS * ( CHASSIS_AXIS_X + CHASSIS_AXIS_Y );
  double right = SENS * ( CHASSIS_AXIS_X - CHASSIS_AXIS_Y );

  if(LEFT_SHIFT)                                shift(-100, 100);
  else if(RIGHT_SHIFT)                          shift(100, -100);
  else if(fabs(left) > 17 && fabs(right) > 17)  chassis(left, right);
  else                                          chassis(0, 0);
}

void grab_manual()
{
  if(GRAB_IN)               grab_in(GRAB_V);
  else if(GRAB_OUT)         grab_out(GRAB_V);
  else                      grab_locked();
}

void lift_manual()
{
  if(BUTTON_UP)
  {
    lift_auto();
  }             
  else if(abs(LIFT_AXIS) > 20)
  {
    lift(LIFT_AXIS);
  }   
  else lift_locked();
}

void arm_h1()
{
  double err = ARM_H1;
  double k = 0.7;
  double sign = 1;

  if(AR_DEG > ARM_H1) sign = -1;

  while(err > 3)
  {
    err = fabs(ARM_H1 - AR_DEG);
    m(motorAR, err * k * sign);
    if(LT_DEG < 200) m(motorLT, 100);
    else lift_locked();
  }
}

void arm_h2()
{
  double err = ARM_H2;
  double k = 0.7;
  double sign = 1;

  if(AR_DEG > ARM_H1) sign = -1;
  while(err > 3)
  {
    err = fabs(ARM_H2 - AR_DEG);
    m(motorAR, err * k * sign);
  }
}

void arm_manual()
{
  if(ARM_UP)                          arm_up(ARM_V);
  else if(ARM_DOWN)                   arm_down(ARM_V);
  else if(ARM_HIGH)                   arm_h2();
  else if(ARM_LOW)                    arm_h1();
  else if(motorAR.rotation(deg) < 157) m(motorAR, -10, 7);
  else arm_locked();         
}
             
void self_check()
{
  while(true)
  {
    Brain.Screen.setPenColor(color::white);
    Brain.Screen.setFont(fontType::mono20);

    int numMotor = vexDevicesGetNumberByType(V5_DeviceType::kDeviceTypeMotorSensor);
    int numInert = vexDevicesGetNumberByType(V5_DeviceType::kDeviceTypeImuSensor);

    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("Number of motor installed: %d", numMotor);
    Brain.Screen.newLine();

    motorLF.installed() ? Brain.Screen.setPenColor(green) : Brain.Screen.setPenColor(red);
    Brain.Screen.print("Name: motorLF   Port: %2d   isInstalled: %s", motorLF.index() + 1, motorLF.installed() ? "true" : "false");
    Brain.Screen.newLine();

    motorLB.installed() ? Brain.Screen.setPenColor(green) : Brain.Screen.setPenColor(red);
    Brain.Screen.print("Name: motorLB   Port: %2d   isInstalled: %s", motorLB.index() + 1, motorLB.installed() ? "true" : "false");
    Brain.Screen.newLine();

    motorRF.installed() ? Brain.Screen.setPenColor(green) : Brain.Screen.setPenColor(red);
    Brain.Screen.print("Name: motorRF   Port: %2d   isInstalled: %s", motorRF.index() + 1, motorRF.installed() ? "true" : "false");
    Brain.Screen.newLine();

    motorRB.installed() ? Brain.Screen.setPenColor(green) : Brain.Screen.setPenColor(red);
    Brain.Screen.print("Name: motorRB   Port: %2d   isInstalled: %s", motorRB.index() + 1, motorRB.installed() ? "true" : "false");
    Brain.Screen.newLine();

    motorLG.installed() ? Brain.Screen.setPenColor(green) : Brain.Screen.setPenColor(red);
    Brain.Screen.print("Name: motorLG   Port: %2d   isInstalled: %s", motorLG.index() + 1, motorLG.installed() ? "true" : "false");
    Brain.Screen.newLine();

    motorRG.installed() ? Brain.Screen.setPenColor(green) : Brain.Screen.setPenColor(red);
    Brain.Screen.print("Name: motorRG   Port: %2d   isInstalled: %s", motorRG.index() + 1, motorRG.installed() ? "true" : "false");
    Brain.Screen.newLine();

    motorAR.installed() ? Brain.Screen.setPenColor(green) : Brain.Screen.setPenColor(red);
    Brain.Screen.print("Name: motorAR   Port: %2d   isInstalled: %s", motorAR.index() + 1, motorAR.installed() ? "true" : "false");
    Brain.Screen.newLine();

    motorLT.installed() ? Brain.Screen.setPenColor(green) : Brain.Screen.setPenColor(red);
    Brain.Screen.print("Name: motorLT   Port: %2d   isInstalled: %s", motorLT.index() + 1, motorLT.installed() ? "true" : "false");
    
    Brain.Screen.setPenColor(white);
    Brain.Screen.newLine();
    Brain.Screen.print("Number of sensor installed: %d", numInert);
    Brain.Screen.newLine();

    imu.installed() ? Brain.Screen.setPenColor(green) : Brain.Screen.setPenColor(red);
    Brain.Screen.print("Inertial Sensor Port: %2d   isInstalled: %s", imu.index() + 1, imu.installed() ? "true" : "false");
    Brain.Screen.newLine();

    Brain.Screen.setPenColor(white);
    Brain.Screen.print("Press BUTTON_A to skip the self-check...");

    if(numMotor == 8) return;

    if(BUTTON_A) return;
    wait(100, msec);
  }
}

void prepare_session()
{
  self_check();
}
