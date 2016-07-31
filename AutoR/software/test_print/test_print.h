#pragma once

#include <LiquidCrystal.h>

#include <phys253.h>

#include <avr/interrupt.h>

#include "../Ai/Debug.h"
#include "../Ai/LLRobot.h"

using namespace LLRobot;

void setup_m();
 
void loop_m();

LiquidCrystal LCD(26,27,28,16,17,18,19,20,21,22,23);

motorClass motor;

ServoTINAH RCServo0;    // declare variables for up to eight     servos.   Replaced old Servo253 implementation 2015Jan2
ServoTINAH RCServo1; 
ServoTINAH RCServo2;
ServoTINAH RCServo3;


void setup_m()
{
    #include <phys253setup.txt>
    Serial.begin(250000);
}

unsigned long startt = 0;
unsigned long endt = 0;

void loop_m()
{   
    startt = micros();
    for(int i = 0; i < 100; i++){
        Serial.print("Testing Testing");
        Serial.print(i);
    }
    endt = micros();
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println(endt-startt);
    Serial.println("");
    Serial.println("");
    Serial.println("");
    LCD.clear();
    LCD.home();
    LCD.print(endt-startt);
    delay(200);
}

