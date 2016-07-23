
#pragma once

#include <LiquidCrystal.h>

#include <phys253.h>

#include <avr/interrupt.h>

#include "../Ai/Debug.h"
#include "../Ai/LLRobot.h"

using namespace LLRobot;
void setup_m();
 
void loop_m();
void cycle_through_irs();
void testQSD();

void setup_m(){
    #include <phys253setup.txt>
    Serial.begin(9600);
   
    initialize();
    
    Debug::serialPrint("Initialized. Starting up.", Debug::GENERAL); 
 
    LCD.clear(); LCD.home();
    LCD.print("Starting up...");
    delay(50);
}

LiquidCrystal LCD(26,27,28,16,17,18,19,20,21,22,23);

motorClass motor;

ServoTINAH RCServo0;    // declare variables for up to eight     servos.   Replaced old Servo253 implementation 2015Jan2
ServoTINAH RCServo1; 
ServoTINAH RCServo2;
ServoTINAH RCServo3;

void loop_m(){
    cycle_through_irs();
    testQSD();
}

void cycle_through_irs(){
    uint8_t val = 0;
    while(!startbutton()){
        delay(100);
        LCD.clear(); 
        LCD.setCursor(0,0);
        LCD.print("IR index: ");
        LCD.print(val);

        
        LCD.setCursor(0,1);
        LCD.print("Value: ");
        LCD.print(Rel::readCurrentQSD(false));

        if (stopbutton()){
            val++;
            val %= 8;
            Rel::setCurrentQSD((Rel::QSD)val,false);
            delay(3);
            while(stopbutton());
        }
    }
    while(startbutton());
}

void testQSD(){
    int16_t stage = 0;
    while(!startbutton()){
        delay(88);

        if (stopbutton()){
            stage++;
            stage %=2;
            while(stopbutton());
        }

        switch(stage){
            case 0:
                {
                    Rel::setCurrentQSD(Rel::IRLB,false);
                    delay(3);
                    int irlb = Rel::readCurrentQSD(false);
                    Rel::setCurrentQSD(Rel::IRLM,false);
                    delay(3);
                    int irlm = Rel::readCurrentQSD(false);
                    Rel::setCurrentQSD(Rel::IRLF,false);
                    delay(3);
                    int irlf = Rel::readCurrentQSD(false);
                    Rel::setCurrentQSD(Rel::IRLU,false);
                    delay(3);
                    int irlu = Rel::readCurrentQSD(false);

                    LCD.clear();

                    LCD.setCursor(0,0);
                    LCD.print("IRLB");
                    LCD.print(irlb);

                    LCD.setCursor(8,0);
                    LCD.print("IRLM");
                    LCD.print(irlm);

                    LCD.setCursor(0,1);
                    LCD.print("IRLF");
                    LCD.print(irlf);

                    LCD.setCursor(8,1);
                    LCD.print("IRLU");
                    LCD.print(irlu);
                }
                break;
            case 1:
                {
                    Rel::setCurrentQSD(Rel::IRRB,false);
                    delay(3);
                    int irrb = Rel::readCurrentQSD(false);
                    Rel::setCurrentQSD(Rel::IRRM,false);
                    delay(3);
                    int irrm = Rel::readCurrentQSD(false);
                    Rel::setCurrentQSD(Rel::IRRF,false);
                    delay(3);
                    int irrf = Rel::readCurrentQSD(false);
                    Rel::setCurrentQSD(Rel::IRRU,false);
                    delay(3);
                    int irru = Rel::readCurrentQSD(false);

                    LCD.clear();

                    LCD.setCursor(0,0);
                    LCD.print("IRRB");
                    LCD.print(irrb);

                    LCD.setCursor(8,0);
                    LCD.print("IRRM");
                    LCD.print(irrm);

                    LCD.setCursor(0,1);
                    LCD.print("IRRF");
                    LCD.print(irrf);

                    LCD.setCursor(8,1);
                    LCD.print("IRRU");
                    LCD.print(irru);
                }
                break;
        }
    }
    while(startbutton());

}

