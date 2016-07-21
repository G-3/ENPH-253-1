#include <avr/interrupt.h>
#include <LiquidCrystal.h>

#include <phys253.h>

#include "../Ai/Debug.h"

#include "../Ai/World.h"
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
    delay(500);
    
    World::setup();
    LCD.clear(); LCD.home();
    LCD.print("Starting up...2");
    delay(500);
    
    LCD.clear(); LCD.home();
    LCD.print("Starting up...1");
    delay(500);
}
 
uint8_t start=0;
uint8_t base=1;
uint8_t fin=12; 

void loop_m()
{
    if(startbutton()){
        uint8_t choose = knob(7)/16;
        while(!stopbutton()){
            choose = knob(7)/16;
            LCD.clear(); LCD.home();
            LCD.print("Start:"); LCD.print(choose);
            LCD.setCursor(0, 1);
            LCD.print("Prev:"); LCD.print(start); 
            delay(20);
        }
        start = choose;
        delay(250);

        while(!stopbutton()){
            choose = knob(7)/16;
            LCD.clear(); LCD.home();
            LCD.print("Base:"); LCD.print(choose);
            LCD.setCursor(0, 1);
            LCD.print("Prev:"); LCD.print(base); 
        }
        base = choose;
        delay(250);

        while(!stopbutton()){
            choose = knob(7)/16;
            LCD.clear(); LCD.home();
            LCD.print("Fin:"); LCD.print(choose);
            LCD.setCursor(0, 1);
            LCD.print("Prev:"); LCD.print(fin); 
        }
        fin = choose;
        delay(250);
    }

    World::updatePath(base, fin);
    HLRobot::lastNode = World::nodes[start];
    HLRobot::baseNode = World::nodes[base];
    HLRobot::destNode = HLRobot::path[1];

    Event::EDetect::getInstance()->step();
    Control::Controller::getInstance()->step();
    //testQRDs();
}
