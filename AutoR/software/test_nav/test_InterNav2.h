#pragma once

#include <LiquidCrystal.h>

#include <phys253.h>

#include <avr/interrupt.h>

#include "../Ai/EDetect.h"
#include "../Ai/Control/Controller.h"
#include "../Ai/Control/TapeFollow2.h"
#include "../Ai/Control/InterNav2.h"
#include "../Ai/Debug.h"
#include "../Ai/LLRobot.h"
#include "../Ai/HLRobot.h"
#include "../Ai/World.h"

using namespace LLRobot;

void setup_m();
 
void loop_m();
void testIntersect();

LiquidCrystal LCD(26,27,28,16,17,18,19,20,21,22,23);

motorClass motor;

ServoTINAH RCServo0;    // declare variables for up to eight     servos.   Replaced old Servo253 implementation 2015Jan2
ServoTINAH RCServo1; 
ServoTINAH RCServo2;
ServoTINAH RCServo3;

void setup_m(){
    #include <phys253setup.txt>
    Serial.begin(9600);
   
    initialize();
    World::setup();
    
    Debug::serialPrint("Initialized. Starting up.", Debug::GENERAL); 
 
    LCD.clear(); LCD.home();
    LCD.print("Starting up...");
    delay(50);
}
void loop_m(){
    testIntersect();
}

void testIntersect(){
    Control::TapeFollow2* tf = new Control::TapeFollow2(17,25,100);
    bool vals[4] = {0,0,0,0};
    Control::InterNav2* in2 = new Control::InterNav2(vals,World::DirL,80,80,80);
    while(!startbutton());
    LLRobot::flip();

    LCD.clear(); LCD.home();
    LCD.print("TapeFollowing...");
    while(!Event::EDetect::getInstance()->checkIntersect()){
        tf->step();
        if (stopbutton()){
            break;
        }
    }
    LCD.clear(); LCD.home();
    LCD.print("Navigating Intersect...");
    while(!stopbutton()){
        in2->step();
    }
    while (!stopbutton());
}
