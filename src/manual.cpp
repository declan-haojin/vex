#include "manual.h"
#include "base.h"

void chassis_manual()
{
  double left = SENS * ( CHASSIS_AXIS_X + CHASSIS_AXIS_Y );
  double right = SENS * ( CHASSIS_AXIS_X - CHASSIS_AXIS_Y );

  if(BUTTON_LEFT)                               shift(-100, 100);
  else if(BUTTON_RIGHT)                         shift(100, -100);
  else if(fabs(left) > 17 && fabs(right) > 17)  chassis(left, right);
  else                                          chassis(0, 0);
}

void grab_manual()
{
  if(GRAB_IN)               grab_in(GRAB_V);
  else if(GRAB_OUT)         grab_out(GRAB_V);
  else                      grab_locked();
}

bool flag = false;

int lift_auto_down_callback()
{
  while(flag)
  {
    while(fabs(LT_DEG) < LIFT_MAX - 7)
    {
      if(fabs(LT_DEG) < 100) lift_down(50);
      else lift_down(100);
    }
    lift_locked();
    flag = false;
  }
  return 0;
}

void lift_manual()
{
  if(BUTTON_UP)
  {
    lift_auto();
  }             
  else if(BUTTON_DOWN)      
  {
    flag = true;
  }
  else if(abs(LIFT_AXIS) > 20)
  {
    lift(LIFT_AXIS);
  }   
  else lift_locked();
}

void arm_manual()
{
  if(ARM_UP)                          arm_up(ARM_V);
  else if(ARM_DOWN)                   arm_down(ARM_V);
  else if(motorAR.rotation(deg) < 157) m(motorAR, -10, 7);
  else arm_locked();         
}

int greatestPitchAngle = 0;
int detect_greatest_pitch_angle_callback()
{
  while(true)
  {
    double tmpPitch = imu.pitch();
    controller1.Screen.clearScreen();
    controller1.Screen.setCursor(1, 1);
    controller1.Screen.print("Current pitch:  %f", tmpPitch);
    controller1.Screen.newLine();
    controller1.Screen.print("Greatest pitch: %f", tmpPitch > greatestPitchAngle ? tmpPitch : greatestPitchAngle);
    
    if(tmpPitch > greatestPitchAngle) greatestPitchAngle = tmpPitch;
    wait(0.1, sec);
  }
  return 0;
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
    Brain.Screen.print("Press BUTTON_DOWN to skip the self-check...");

    if(numMotor == 8) return;

    if(BUTTON_DOWN) return;
    wait(100, msec);
  }
}

void prepare_session()
{
  self_check();
}
