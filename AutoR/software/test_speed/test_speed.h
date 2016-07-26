#include <avr/interrupt.h>
#include <LiquidCrystal.h>

#include <phys253.h>
#include "../Ai/Debug.h"
#include "../Ai/LLRobot.h"

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
    while (true){
        delay(100);
        uint32_t t1 = micros();
        uint16_t val = analogRead(0);
        uint32_t t2 = micros();
        LCD.clear(); LCD.home();
        LCD.print(t2-t1);
        LCD.setCursor(0,1);
        LCD.print(val);
    }
            
}

