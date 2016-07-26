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
    LCD.clear(); LCD.home();
    LCD.print("Starting up...2");
    delay(200);
    
    LCD.clear(); LCD.home();
    LCD.print("Starting up...1");
    delay(200);
    
    Serial.println("updating");

    World::Node *start = World::nodes[0];
    World::Node *base = World::nodes[1];
    World::updatePath(1, 10);
}

unsigned long startt=0;
unsigned long endt=0;

void loop_m()
{
    Event::EDetect::getInstance()->step();
    Control::Controller::getInstance()->step();   
    //startt = micros(); 
    //endt = micros();
    //Serial.println(endt);
    //Serial.println(startt);
    //int counter = 1;
    
/*
    while (HLRobot::path[counter]){
        Serial.print(counter);
        Serial.print(" ");
        Serial.println(HLRobot::path[counter]->id);
        
        dest = HLRobot::path[counter];
        
        Serial.print("Destination Node:");
        Serial.println(dest->id);

        bool expectTapeDir[4]={false, false, false, false};
        base->relLinkDirs(expectTapeDir, start);
        int destDir = base->relDestDir(dest, start);
        Debug::serialPrint("Direction . Exp Tape \n", Debug::INTERSECT_DB);
        for(int i = 0; i < 4; i++){
            char msg[20];
            sprintf(msg, "%d . %d \n", i, expectTapeDir[i]);
            Debug::serialPrint(msg, Debug::INTERSECT_DB);
        }
        char msg[20];
        sprintf(msg, "Dest Dir %d \n", destDir);
        Debug::serialPrint(msg, Debug::INTERSECT_DB);   
        Serial.println(destDir); 
        counter += 1;
        start = base;
        base = dest;

    }
*/
    delay(1000);
    
    // Event::EDetect::getInstance()->step();
    // Control::Controller::getInstance()->step();
    // testQRDs();
}
