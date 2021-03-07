#include "myVision.h"
#include "base.h"
#include "vision.h"

bool isBlueFound() {
  Vision.takeSnapshot(BLUE_BALL);
  if(Vision.objectCount > 0 && Vision.objects[0].width > 150 && Vision.objects[0].height > 100) return true;
  return false;
}

bool isRedFound() {
  Vision.takeSnapshot(RED_BALL);
  if(Vision.objectCount > 0 && Vision.objects[0].width > 150 && Vision.objects[0].height > 100) return true;
  return false;
}

vision::signature COLOR = BLUE_BALL;
vision::object none = vision::object();
bool isFound = false;

vision::object basket()
{
  Vision.takeSnapshot(COLOR);
  int cnt = Vision.objectCount;
  for(int i=0; i<cnt; i++)
  {
    if(Vision.objects[i].centerY > 130 && Vision.objects[i].centerY < 160)
    {
      isFound = true;
      return Vision.objects[i];
    }
  } 
  return none;
}

int colorChange()
{
  while(true)
  {
    Vision.setLedColor(0, 0, 255);
    wait(0.5, sec);
    Vision.setLedColor(255, 0, 0);
    wait(0.5, sec);
    Vision.setLedColor(0, 255, 0);
    wait(0.5, sec);
  }
  return 0;
}

void approach(double totalDis, double pw)
{
  task ColorChange = task(colorChange);
  Vision.setBrightness(66);
  Vision.setLedColor(0, 255, 0);
  chassis_reset();
  float kp = 0.9;
  float vx = 0;
  float xlasterror;
  while(true)
  {
    double turnPower;
    isFound = false;
    vision::object tmp = basket();

    double currentDis = (LF_DEG + LB_DEG + RF_DEG + RB_DEG) * 0.25;
    double disErr = fabs(totalDis) - fabs(currentDis);
    int xCoord = tmp.centerX; 
    vx = xCoord - xlasterror;
    xlasterror = xCoord;

    turnPower = xCoord * kp + xCoord * vx;

    if(!isFound)
    {
      chassis(pw, pw);
    }
    else
    {
      chassis(pw + turnPower, pw - turnPower);
    }

    if(disErr < 3) break;
    

    wait(20, msec);
  }
  chassis(0, 0);
}

