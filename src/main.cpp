#include "base.h"
#include "manual.h"
#include "auto.h"
#include "myVision.h"

using namespace vex;

competition Competition;

void pre_auton(void) {
  is_chassis_brake_mood(true);
  chassis_reset();
  inert_reset();
}

void autonomous(void) {
  approach(3000, 57.7);
}

void usercontrol(void) {
  task detect_greatest_pitch_angle = task(detect_greatest_pitch_angle_callback);
  bool preSession = true;

  while (1) {
    if(preSession)
    {
      prepare_session();
      preSession = false;
    }
    else
    {
      chassis_manual();
      lift_manual();
      wait(20, msec); 
      #ifdef DEV
      if(BUTTON_X)
      {
        chassis_run(5000, 77.7, 0);
      }
      else if(BUTTON_Y)
      {
        inert_reset();
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