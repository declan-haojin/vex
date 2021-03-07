#include "manual.h"
#include "base.h"

void chassis_manual()
{
  double left = SENS * ( AXIS_3 + AXIS_4 );
  double right = SENS * ( AXIS_3 - AXIS_4 );
  if(inert.pitch() > 20.7)
  {
    while(inert.pitch() > 7)
    {
      m(motorLB, -70);
      m(motorRB, -70);
    }
    m(motorLB, 0);
    m(motorRB, 0);
    
  }
  else if(inert.pitch() < -20.7)
  {
    while(inert.pitch() < -7)
    {
      m(motorLF, 70);
      m(motorRF, 70);
    }
    m(motorLF, 0);
    m(motorRF, 0);
  }
  else
  {
    chassis(left, right);
  }
  
}

void lift_manual()
{
  if(LOWER_KEY_UP)
  {
    grab_in(100);
  }
  else if(LOWER_KEY_DOWN)
  {
    grab_out(100);
  }
  else
  {
    grab_locked();
  }
  
  if((BUTTON_L1 && BUTTON_L2) || BUTTON_Y)
  {
    low_lift_up(70);
  }
  else if(LOWER_KEY_UP)
  {
    low_lift_up(-100);
  }
  else if(LOWER_KEY_DOWN) 
  {
    low_lift_down(-100);
  }
  else if (UPPER_KEY_UP) 
  {
    low_lift_up(100);
  }
  else if (UPPER_KEY_DOWN) 
  {
    low_lift_down(100);
  }
  else
  {
    low_lift_locked();
  }

  if((BUTTON_L1 && BUTTON_L2) || BUTTON_Y)
  {
    high_lift_down(100);
  }
  else if(UPPER_KEY_UP)
  {
    high_lift_up(100);
  }
  else if(UPPER_KEY_DOWN)
  {
    high_lift_down(100);
  }
  else
  {
    high_lift_locked();
  }
}

void vision_manual()
{
  if(isBlueFound())
  {
    Brain.Screen.setFont(mono40);
    Brain.Screen.clearLine(3, black);
    Brain.Screen.setCursor(Brain.Screen.row(), 1);
    Brain.Screen.setCursor(3, 1);
    Brain.Screen.print("Blue Ball Found");
  }
  else if(isRedFound())
  {
    Brain.Screen.setFont(mono40);
    Brain.Screen.clearLine(5, black);
    Brain.Screen.setCursor(Brain.Screen.row(), 1);
    Brain.Screen.setCursor(5, 1);
    Brain.Screen.print("Red Ball Found");
  }
  else
  {
    Brain.Screen.clearScreen();
  }
}

int greatestPitchAngle = 0;
int detect_greatest_pitch_angle_callback()
{
  while(true)
  {
    double tmpPitch = inert.pitch();
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

    motorLL.installed() ? Brain.Screen.setPenColor(green) : Brain.Screen.setPenColor(red);
    Brain.Screen.print("Name: motorLL   Port: %2d   isInstalled: %s", motorLL.index() + 1, motorLL.installed() ? "true" : "false");
    Brain.Screen.newLine();

    motorHL.installed() ? Brain.Screen.setPenColor(green) : Brain.Screen.setPenColor(red);
    Brain.Screen.print("Name: motorHL   Port: %2d   isInstalled: %s", motorHL.index() + 1, motorHL.installed() ? "true" : "false");
    
    Brain.Screen.setPenColor(white);
    Brain.Screen.newLine();
    Brain.Screen.print("Number of sensor installed: %d", numInert);
    Brain.Screen.newLine();

    inert.installed() ? Brain.Screen.setPenColor(green) : Brain.Screen.setPenColor(red);
    Brain.Screen.print("Inertial Sensor Port: %2d   isInstalled: %s", inert.index() + 1, inert.installed() ? "true" : "false");
    Brain.Screen.newLine();

    Brain.Screen.setPenColor(white);
    Brain.Screen.print("Press BUTTON_DOWN to skip the self-check...");

    if(numMotor == 8 && numInert == 1) return;

    if(BUTTON_DOWN) return;
    wait(100, msec);
  }
}

void prepare_session()
{
  self_check();
}
