
#pragma once

#include <LiquidCrystal.h>

#include <phys253.h>

#include <avr/interrupt.h>

#include "../Ai/Debug.h"
#include "../Ai/LLRobot.h"
#include "../Ai/Control/Pickup.h"

using namespace LLRobot;

void setup_m();
 
void loop_m();

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
    
    Debug::serialPrint("Initialized. Starting up.", Debug::GENERAL); 
 
    LCD.clear(); LCD.home();
    LCD.print("Starting up...");
    delay(50);
}

void loop_m(){
    Control::Pickup pickup = Control::Pickup(RIGHT,Control::Pickup::SETUP);

    while (!startbutton()){
    }
    while (startbutton());
    LCD.clear(); LCD.home();
    LCD.print("Picking Up...");
    while(!stopbutton()){
        pickup.step();
        delay(1);

    }
    while(stopbutton()){
        Rel::openClaw(Rel::CR,true);
        Rel::openClaw(Rel::CL,true);
        delay(50);

    }
    LCD.clear(); LCD.home();
    LCD.print("Done!");
    delay(500);
    
}
