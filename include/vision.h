/*vex-vision-config:begin*/
#include "vex.h"
vex::vision::signature BLUE_BALL = vex::vision::signature (1, -2979, -2123, -2550, 6333, 8391, 7362, 2.5, 0);
vex::vision::signature RED_BALL = vex::vision::signature (2, 5993, 9039, 7516, -841, -241, -542, 3, 0);
vex::vision::signature SIG_3 = vex::vision::signature (3, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_4 = vex::vision::signature (4, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_5 = vex::vision::signature (5, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_6 = vex::vision::signature (6, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_7 = vex::vision::signature (7, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision Vision = vex::vision (vex::PORT5, 66, BLUE_BALL, RED_BALL, SIG_3, SIG_4, SIG_5, SIG_6, SIG_7);
/*vex-vision-config:end*/