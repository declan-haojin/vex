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
  red_close();
}

void usercontrol(void) {
  // task detect_greatest_pitch_angle = task(detect_greatest_pitch_angle_callback);
  bool preSession = true;
  while (1) {
    if(preSession)
    {
      // prepare_session();
      preSession = false;
    }
    else
    {
      controller1.Screen.clearScreen();
      controller1.Screen.setCursor(1, 1);
      controller1.Screen.print("imu: %3f", imu.rotation());
      controller1.Screen.newLine();
      controller1.Screen.print("lift:%3f", motorLT.rotation(deg));
      controller1.Screen.newLine();
      controller1.Screen.print("dist:%3f", (LB_DEG+LF_DEG+RF_DEG+RB_DEG)*0.25);
      chassis_manual();
      lift_manual();
      grab_manual();
      arm_manual();
      wait(20, msec); 
      #ifdef DEV
      if(BUTTON_X)
      {
        

        // chassis(80, 80);
        // lift_reset();
        // grab_in(100);
        red_close();
        // chassis_run(1000, 1, 0);
        // imu_reset();
        // chassis_turn(135.7);
      }
      else if(BUTTON_Y)
      {
        imu_reset();
        motorLT.resetRotation();
        chassis_reset();
        lift_reset();
      }
      #endif
    }
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