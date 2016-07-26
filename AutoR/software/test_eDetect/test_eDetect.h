
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
void testIR();
void testBumpers();

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
    testIR();
    testBumpers();
}

void testID(){
    bool intersectionDetected = false;
    int16_t counter = 0;
    while(!startbutton()){
        delay(1);
        counter %= 10;
        int32_t t1 = micros();
        bool val = Event::EDetect::getInstance()->checkIntersect();
        int32_t t2 = micros();
        intersectionDetected |= val;
        if (counter == 0){
            if (intersectionDetected == false){
                LCD.clear(); LCD.home();
                LCD.print("Intersect: False");
            }else{
                LCD.clear(); LCD.home();
                LCD.print("Intersect: True");
            }
            LCD.setCursor(0,1);
            LCD.print(t2-t1);

        }

        if (stopbutton()){
            intersectionDetected = false;
        }
        
        Serial.println(val);
        counter++;
    }
    while(startbutton());
}

void testIR(){
    bool irDetected = false;
    int16_t counter = 0;
    while(!startbutton()){
        delay(1);
        counter %= 10;
        int32_t t1 = micros();
        bool val = Event::EDetect::getInstance()->checkIntersect();
        int32_t t2 = micros();
        irDetected |= val;
        if (counter == 0){
            if (irDetected == false){
                LCD.clear(); LCD.home();
                LCD.print("IR: False");
            }else{
                LCD.clear(); LCD.home();
                LCD.print("IR: True");
            }
            LCD.setCursor(0,1);
            LCD.print(t2-t1);

        }

        if (stopbutton()){
            irDetected = false;
        }
        
        Serial.println(val);
        counter++;
    }
    while(startbutton());

}

void testBumpers(){
    bool collisionDetected = false;
    int16_t counter = 0;
    while(!startbutton()){
        delay(1);
        counter %= 10;
        int32_t t1 = micros();
        bool val = Event::EDetect::getInstance()->checkBumpers();
        int32_t t2 = micros();
        collisionDetected |= val;
        if (counter == 0){
            if (collisionDetected == false){
                LCD.clear(); LCD.home();
                LCD.print("Bumpers: False");
            }else{
                LCD.clear(); LCD.home();
                LCD.print("Bumpers: True");
            }
            LCD.setCursor(0,1);
            LCD.print(t2-t1);
        }
        
        Serial.println(val);
        counter++;

        if (stopbutton()){
            collisionDetected = false;
        }
    }
    while(startbutton());
}

