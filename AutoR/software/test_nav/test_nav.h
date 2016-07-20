#include <avr/interrupt.h>
#include <LiquidCrystal.h>

#include <phys253.h>

#include "../Ai/Debug.h"

#include "../Ai/EDetect.h"
#include "../Ai/LLRobot.h"
#include "../Ai/Control/Controller.h"
#include "../Ai/HLRobot.h"

#define ledPin 13

LiquidCrystal LCD(26,27,28,16, 17, 18, 19,20,21,22,23);

motorClass motor ;

ServoTINAH RCServo0;    // declare variables for up to eight     servos.   Replaced old Servo253 implementation 2015Jan2
ServoTINAH RCServo1; 
ServoTINAH RCServo2;
ServoTINAH RCServo3;

void setup_m()
{
    #include <phys253setup.txt>
    Serial.begin(9600);
   
    pinMode(8, OUTPUT);
    
    Debug::serialPrint("Initialized. Starting up.", Debug::GENERAL); 
 
    LCD.clear(); LCD.home();
    LCD.print("Starting up...3");
    delay(1000);
    
    World::setup();
    HLRobot::lastNode = nodes[0];
    HLRobot::baseNode = nodes[1];
    HLRobot::destNode = nodes[4];

    LCD.clear(); LCD.home();
    LCD.print("Starting up...2");
    delay(1000);
    
    LCD.clear(); LCD.home();
    LCD.print("Starting up...1");
    delay(1000);
}
 
void loop_m()
{
    Event::EDetect::getInstance()->step();
    Control::Controller::getInstance()->step();
    delay(500);
    //testQRDs();
}