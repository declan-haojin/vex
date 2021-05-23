#include "base.h"
#include "manual.h"
#include "auto.h"
#include "myVision.h"

using namespace vex;

competition Competition;

void pre_auton(void) {
  set_chassis_brake_mood(true);
  chassis_reset();
  imu_reset();
  motorAR.resetRotation();
}

void autonomous(void) {
  
}

void usercontrol(void) {
  bool preSession = true;
  bool isAuto = false;
  while (1) {
    if(preSession)
    {
      prepare_session();
      preSession = false;
    }
    else
    {
      if(swc.value() == false && isAuto == false)
      {
        // chassis_reset();
        // motorAR.resetRotation();
        // imu_reset();
        // lift_reset();
        // chassis_turn(180);
        wait(0.3, sec);
        isAuto = true;
        // red_far();
        blue_far();
        // chassis_turn(-150);
      }
      if(BUTTON_Y)
      {
        imu_reset();
        lift_reset();
        chassis_reset();
        motorAR.resetRotation();
      }

      chassis_manual();
      lift_manual();
      grab_manual();
      arm_manual();

      // controller1.Screen.clearScreen();
      // controller1.Screen.setCursor(1, 1);
      // controller1.Screen.print("imu: %3f", imu.rotation());
      // // controller1.Screen.newLine();
      // controller1.Screen.print("lift:%3f", motorLT.rotation(deg));
      // // controller1.Screen.newLine();
      // // controller1.Screen.print("dist:%3f", (LB_DEG+LF_DEG+RF_DEG+RB_DEG)*0.25);
      // controller1.Screen.newLine();
      // controller1.Screen.print("arm: %3f", AR_DEG);
    }
    wait(20, msec); 
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while (true) {
    wait(100, msec);
  }
}