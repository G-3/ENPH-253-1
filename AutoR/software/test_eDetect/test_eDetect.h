
#pragma once

#include <LiquidCrystal.h>

#include <phys253.h>

#include <avr/interrupt.h>

#include "../Ai/Debug.h"
#include "../Ai/LLRobot.h"
#include "../EDetect.h"

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

void loop_m();
{
    testID();
}

void testID{
    bool intersectionDetected = false;
    int16_t counter = 0;
    while(!startbutton()){
        delay(1);
        counter++;
        counter %= 100;
        if (counter == 0){
            if (intersectionDetected == false){
                LCD.clear(); LCD.home();
                LCD.print("True");
            }else{
                LCD.clear(); LCD.home();
                LCD.print("False");
            }
        }
        if(Event::checkIntersect){
            bool intersectionDetected = true;
        }
    }
    while(startbutton());
}

