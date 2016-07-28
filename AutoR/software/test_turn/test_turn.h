#pragma once

#include <LiquidCrystal.h>

#include <phys253.h>

#include <avr/interrupt.h>

#include "../Ai/Debug.h"
#include "../Ai/LLRobot.h"
#include "../Ai/Control/TurnAround.h"
#include "../Ai/Control/Controller.h"

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
    while (!startbutton()){
    }
    LCD.print("Checking...");
    LLRobot::Rel::driveMotors(60,60);
    while (!LLRobot::Rel::readBumper(LLRobot::Rel::BF));
    LCD.clear(); LCD.home();
    LCD.print("Turning Around...");
    Control::Controller::getInstance()->setNextController(new Control::TurnAround());
    while(!stopbutton()){
        Control::Controller::getInstance()->step();
        delay(1);
    }
    LCD.clear(); LCD.home();
    LCD.print("Done!");
    delay(500);
    
}
