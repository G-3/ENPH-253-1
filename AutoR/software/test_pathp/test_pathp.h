#pragma once
#include <LiquidCrystal.h>

#include <phys253.h>

#include <avr/interrupt.h>

#include "../Ai/Debug.h"

#include "../Ai/EDetect.h"
#include "../Ai/LLRobot.h"
#include "../Ai/Control/Controller.h"
#include "../Ai/World.h"
#include "../Ai/HLRobot.h"

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
    delay(200);
    
    World::setup();
    HLRobot::lastNode = World::nodes[0];
    HLRobot::baseNode = World::nodes[1];
    HLRobot::destNode = World::nodes[4];

    LCD.clear(); LCD.home();
    LCD.print("Starting up...2");
    delay(200);
    
    LCD.clear(); LCD.home();
    LCD.print("Starting up...1");
    delay(200);
    
    Serial.println("updating");

}

unsigned long start=0;
unsigned long end=0;

void loop_m()
{   
    start = micros(); 
    World::updatePath(8, 18);
    end = micros();
    Serial.println(end);
    Serial.println(start);
    int counter = 0;
    while (HLRobot::path[counter]){
        counter += 1;
        Serial.print(counter);
        Serial.print(" ");
        Serial.println(HLRobot::path[counter]->id);
    }
    delay(1000);
    // Event::EDetect::getInstance()->step();
    // Control::Controller::getInstance()->step();
    // testQRDs();
}
