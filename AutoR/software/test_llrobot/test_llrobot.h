#pragma once

#include <LiquidCrystal.h>

#include <phys253.h>
#include "test_llrobot.h"

#include <avr/interrupt.h>

#include "../Ai/Debug.h"
#include "../Ai/LLRobot.h"

using namespace LLRobot;

void setup_m();
 
void loop_m();
bool setOrientation();
void testQRD();
void testQSD();
void testTripSensors();
void testArms();
void testClaws();

LiquidCrystal LCD(26,27,28,16,17,18,19,20,21,22,23);

motorClass motor;

ServoTINAH RCServo0;    // declare variables for up to eight     servos.   Replaced old Servo253 implementation 2015Jan2
ServoTINAH RCServo1; 
ServoTINAH RCServo2;
ServoTINAH RCServo3;


void setup_m()
{
    #include <phys253setup.txt>
    Serial.begin(9600);
   
    initialize();
    
    Debug::serialPrint("Initialized. Starting up.", Debug::GENERAL); 
 
    LCD.clear(); LCD.home();
    LCD.print("Starting up...");
    delay(50);
}

void loop_m()
{   
    setOrientation();
    testQRD();
    testQSD();
    testTripSensors();
    testArms();
    testClaws();

    LCD.clear(); LCD.home();
    LCD.print("Done!");
    delay(200);
}
bool setOrientation(){
    while(!startbutton()){
        delay(100);
        LCD.clear();
        LCD.home();
        LCD.print("Orientation:");
        LCD.setCursor(0,1);
        if(getOrientation() == FORWARDS){
            LCD.print("Forwards");
        }
        else{
            LCD.print("Backwards");
        }

        if (stopbutton()){
            flip();
            while(stopbutton());
        }
    }
    while(startbutton());
}


void testQRD(){
    int16_t stage = 0;
    int16_t speed = 250;
    while(!startbutton()){
        delay(100);
        
        Rel::driveMotors(speed, speed);
        if (stopbutton()){
            stage++;
            stage %=3;
            while(stopbutton());
        }

        switch(stage){
            case 0:
                {
                int16_t tflf = Rel::readQRD(Rel::TFLF);
                int16_t tfrf = Rel::readQRD(Rel::TFRF);
                int16_t idlf = Rel::readQRD(Rel::IDLF);
                int16_t idrf = Rel::readQRD(Rel::IDRF);

                LCD.clear();

                LCD.setCursor(0,0);
                LCD.print("TFLF");
                LCD.print(tflf);

                LCD.setCursor(8,0);
                LCD.print("TFRF");
                LCD.print(tfrf);

                LCD.setCursor(0,1);
                LCD.print("IDLF");
                LCD.print(idlf);

                LCD.setCursor(8,1);
                LCD.print("IDRF");
                LCD.print(idrf);
                }
                break;
            case 1:
                {
                int16_t tflb = Rel::readQRD(Rel::TFLB);
                int16_t tfrb = Rel::readQRD(Rel::TFRB);
                int16_t idlb = Rel::readQRD(Rel::IDLB);
                int16_t idrb = Rel::readQRD(Rel::IDRB);

                LCD.clear();

                LCD.setCursor(0,0);
                LCD.print("TFLB");
                LCD.print(tflb);

                LCD.setCursor(8,0);
                LCD.print("TFRB");
                LCD.print(tfrb);

                LCD.setCursor(0,1);
                LCD.print("IDLB");
                LCD.print(idlb);

                LCD.setCursor(8,1);
                LCD.print("IDRB");
                LCD.print(idrb);
                }
                break;
            case 2:
                {
                int16_t inl = Rel::readQRD(Rel::INL);
                int16_t inr = Rel::readQRD(Rel::INR);

                LCD.clear();

                LCD.setCursor(0,0);
                LCD.print("INL");
                LCD.print(inl);

                LCD.setCursor(8,0);
                LCD.print("INR");
                LCD.print(inr);
                }
                break;
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

void testTripSensors(){
    while(!startbutton()){
        delay(100);

        bool atl = Rel::readArmTrip(Rel::ATL);
        bool atr = Rel::readArmTrip(Rel::ATR);
        bool bf = Rel::readBumper(Rel::BF);
        bool bb = Rel::readBumper(Rel::BB);

        LCD.clear();

        LCD.setCursor(0,0);
        LCD.print("ATL");
        LCD.print(atl);

        LCD.setCursor(8,0);
        LCD.print("ATR");
        LCD.print(atr);

        LCD.setCursor(0,1);
        LCD.print("BF");
        LCD.print(bf);

        LCD.setCursor(8,1);
        LCD.print("BB");
        LCD.print(bb);

    }
    while(startbutton());
}

void testArms(){
    Side side = LEFT;
    while(!startbutton()){
        delay(100);
        int angle = knob(6)/5;

        LCD.clear();
        LCD.home();
        LCD.print("Angle: ");
        LCD.print(angle);
        if (stopbutton()){
            if (side == LEFT){
                side = RIGHT;
            }else{
                side = LEFT;
            }
            while(stopbutton());
        }
        if (side == LEFT){
            LCD.setCursor(0,1);
            LCD.print("Left");
            Rel::extendArm(Rel::AL,angle);
        }else{
            LCD.setCursor(0,1);
            LCD.print("Right");
            Rel::extendArm(Rel::AR,angle);
        }
    }
    while(startbutton());
}
void testClaws(){
    Side side = LEFT;
    while(!startbutton()){
        delay(100);
        bool isOpen = knob(6) < 512;
        LCD.clear();
        LCD.home();
        LCD.print("isOpen: ");
        LCD.print(isOpen);

        if (stopbutton()){
            if (side == LEFT){
                side = RIGHT;
            }else{
                side = LEFT;
            }
            while(stopbutton());
        }
        if (side == LEFT){
            LCD.setCursor(0,1);
            LCD.print("Left");
            Rel::openClaw(Rel::CL,isOpen);
        }else{
            LCD.setCursor(0,1);
            LCD.print("Right");
            Rel::openClaw(Rel::CR,isOpen);
        }
    }
    while(startbutton());
}
