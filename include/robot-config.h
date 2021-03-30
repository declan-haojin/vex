using namespace vex;
using namespace std;

#define DEV
#define SENS                            1.0
#define ARM_V                           100
#define GRAB_V                          100
#define LIFT_MAX                        1907

#define MOTOR_LF_PORT                   PORT8
#define MOTOR_LB_PORT                   PORT11
#define MOTOR_RF_PORT                   PORT19
#define MOTOR_RB_PORT                   PORT13
#define MOTOR_LG_PORT                   PORT5
#define MOTOR_RG_PORT                   PORT6
#define MOTOR_LT_PORT                   PORT16
#define MOTOR_AR_PORT                   PORT12  
#define INERTIAL_PORT                   PORT10
#define SWITCH_PORT                     A

#define MOTOR_LF_TYPE                   ratio18_1
#define MOTOR_LB_TYPE                   ratio18_1
#define MOTOR_RF_TYPE                   ratio18_1
#define MOTOR_RB_TYPE                   ratio18_1
#define MOTOR_LG_TYPE                   ratio36_1
#define MOTOR_RG_TYPE                   ratio36_1
#define MOTOR_LT_TYPE                   ratio36_1
#define MOTOR_AR_TYPE                   ratio36_1

extern brain Brain;
extern controller controller1;
extern motor motorLF;
extern motor motorLB;
extern motor motorRF;
extern motor motorRB;
extern motor motorLG;
extern motor motorRG;
extern motor motorLT;
extern motor motorAR;
extern motor_group chassisLeft;
extern motor_group chassisRight;
extern motor_group grab;
extern inertial imu;
extern digital_in swc;