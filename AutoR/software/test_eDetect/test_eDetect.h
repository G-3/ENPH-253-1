
#pragma once

#include <LiquidCrystal.h>

#include <phys253.h>

#include <avr/interrupt.h>

#include "../Ai/Debug.h"
#include "../Ai/LLRobot.h"
#include "../Ai/EDetect.h"

#define ledPin 13

LiquidCrystal LCD(26,27,28,16, 17, 18, 19,20,21,22,23);

motorClass motor ;

ServoTINAH RCServo0;    // declare variables for up to eight     servos.   Replaced old Servo253 implementation 2015Jan2
ServoTINAH RCServo1; 
ServoTINAH RCServo2;
ServoTINAH RCServo3;


using namespace LLRobot;
void setup_m();
 
void loop_m();
void testID();

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
    testID();
}

void testID(){
    bool intersectionDetected = false;
    int16_t counter = 0;
    while(!startbutton()){
        delay(1);
        counter %= 10;
        int32_t t1 = micros();
        bool val = Event::checkIntersect();
        int32_t t2 = micros();
        intersectionDetected |= val;
        if (counter == 0){
            if (intersectionDetected == false){
                LCD.clear(); LCD.home();
                LCD.print("False");
            }else{
                LCD.clear(); LCD.home();
                LCD.print("True");
            }
            LCD.setCursor(0,1);
            LCD.print(t2-t1);

        }
        
        Serial.println(val);
        counter++;
    }
    while(startbutton());
}

