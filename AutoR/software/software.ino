// This include statement should be changed to whatever we want to be running 

// Test PathPlanning
// #include "./test_pathp/test_pathp.h"

// Test LowLevel Robot
//#include "./test_llrobot/test_llrobot.h"

// Test Nav, tests navigation.
//#include "./test_nav/test_nav.h"

// Test the QRDs listing them on the LCD one by one
// Multi-paged, use START button to switch between.
// #include "./test_qrd/test_qrd.h"

// Test traversal between two nodes
// #include "./test_trav/test_trav.h"

//Test Pickup
#include "./test_pickup/test_pickup.h"

//Test Irs
//#include "./test_ir/test_ir.h"

//Test Speed
//#include "./test_speed/test_speed.h"

//Test Tape Follow
//#include "./test_tapef/test_tapef2.h"

//Test EDetect
#include "./test_eDetect/test_eDetect.h"

void setup()
{
    setup_m();
}
 
void loop()
{
    loop_m();
}
