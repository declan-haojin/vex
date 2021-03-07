using namespace vex;
using namespace std;

#define DEV
#define SENS                            1.0
#define AXIS_THRESHOLD                  20

#define MOTOR_LF_PORT                   PORT8
#define MOTOR_LB_PORT                   PORT9
#define MOTOR_RF_PORT                   PORT13
#define MOTOR_RB_PORT                   PORT14
#define MOTOR_LG_PORT                   PORT6
#define MOTOR_RG_PORT                   PORT1
#define MOTOR_LL_PORT                   PORT20
#define MOTOR_HL_PORT                   PORT16

#define INERTIAL_PORT                   PORT2
#define SWITCH_PORT                     A
#define LIGHT_PORT                      B

#define MOTOR_LF_TYPE                   ratio6_1
#define MOTOR_LB_TYPE                   ratio6_1
#define MOTOR_RF_TYPE                   ratio6_1
#define MOTOR_RB_TYPE                   ratio6_1
#define MOTOR_LG_TYPE                   ratio18_1
#define MOTOR_RG_TYPE                   ratio18_1
#define MOTOR_LL_TYPE                   ratio6_1
#define MOTOR_HL_TYPE                   ratio6_1

extern brain Brain;
extern controller controller1;
extern motor motorLF;
extern motor motorLB;
extern motor motorRF;
extern motor motorRB;
extern motor motorLG;
extern motor motorRG;
extern motor motorLL;
extern motor motorHL;
extern motor_group chassisLeft;
extern motor_group chassisRight;
extern motor_group grab;
extern inertial inert;
extern digital_in swc;
extern line lit;