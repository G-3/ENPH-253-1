#include <avr/interrupt.h>
#include <LiquidCrystal.h>

#include <phys253.h>

#include "../Ai/Debug.h"

#include "../Ai/World.h"
#include "../Ai/EDetect.h"
#include "../Ai/LLRobot.h"
#include "../Ai/Control/Controller.h"
#include "../Ai/Control/TapeFollow2.h"
#include "../Ai/PathPlan/Planner.h"
#include "../Ai/PathPlan/RegionWalk.h"
#include "../Ai/HLRobot.h"

LiquidCrystal LCD(26,27,28,16, 17, 18, 19,20,21,22,23);

motorClass motor ;

ServoTINAH RCServo0;    // declare variables for up to eight     servos.   Replaced old Servo253 implementation 2015Jan2
ServoTINAH RCServo1; 
ServoTINAH RCServo2;
ServoTINAH RCServo3;

uint8_t initialLast = 10;
uint8_t initialBase = 11;
using namespace PathPlan;

int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

void setup_m()
{
    #include <phys253setup.txt>
    Serial.begin(9600);
    
    // Initializations
    World::setup(); 
    LLRobot::initialize(); 
   
    LCD.clear(); LCD.home();
    LCD.print("RegionW");
    delay(500);

    // Initialize starting positions 
    HLRobot::lastNode = World::nodes[initialLast];
    HLRobot::baseNode = World::nodes[initialBase];
    
    Planner::getInstance()->setNextPlanner(new RegionWalk());
}

int counter = 0;

void loop_m()
{
    Event::EDetect::getInstance()->step();
    Control::Controller::getInstance()->step();
    
    // TODO: Add reliable reset to the test case and tunable start and end destinations
   
    /*
    counter += 1;
    if(counter%20 == 0){
        counter = 0;
        LCD.clear(); LCD.home();
        LCD.print(freeRam());*/
        /*
        if(stopbutton()){
            HLRobot::pathCounter = 0;
            HLRobot::lastNode = World::nodes[0];
            HLRobot::baseNode = World::nodes[1];
            World::updatePath(HLRobot::baseNode->id, ultimateLast); 
            HLRobot::destNode = HLRobot::getNextDest(HLRobot::baseNode);
            HLRobot::curMode = HLRobot::TAPE_FOLLOW;
            Control::Controller::getInstance()->setNextController(new Control::TapeFollow2(17,25,100));
            delay(250);
        }*/
    //}
}
