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

void setup_m()
{
    #include <phys253setup.txt>
    Serial.begin(9600);
   
    LCD.clear(); LCD.home();
    LCD.print("Starting up...3");
    delay(1000);
 
    LCD.clear(); LCD.home();
    LCD.print("Starting up...2");
    delay(1000);
    
    LCD.clear(); LCD.home();
    LCD.print("Starting up...1");
    delay(1000);

    Debug::serialPrint("Initialized. Starting up.", Debug::GENERAL); 
}
 
void loop_m()
{
    // FRONT
    while(!startbutton()){
        int valueTLF = LLRobot::Rel::readQRD(LLRobot::Rel::TFLF, false);
        int valueTRF = LLRobot::Rel::readQRD(LLRobot::Rel::TFRF, false);
        int valueIRF = LLRobot::Rel::readQRD(LLRobot::Rel::IDRF, false);
        int valueILF = LLRobot::Rel::readQRD(LLRobot::Rel::IDLF, false);
        LCD.clear(); LCD.home();
        LCD.print("TLF:"); LCD.print(valueTLF);
        LCD.print(" TRF:"); LCD.print(valueTRF);
        LCD.setCursor(0,1);
        LCD.print("IRF:"); LCD.print(valueIRF);
        LCD.print(" ILF:"); LCD.print(valueILF);
        delay(50);
    }
    delay(250);
    
    // BACK
    while(!startbutton()){
        int valueTLB = LLRobot::Rel::readQRD(LLRobot::Rel::TFLB, false);
        int valueTRB = LLRobot::Rel::readQRD(LLRobot::Rel::TFRB, false);
        int valueILB= LLRobot::Rel::readQRD(LLRobot::Rel::IDLB, false);
        int valueIRB = LLRobot::Rel::readQRD(LLRobot::Rel::IDRB, false);
        LCD.clear(); LCD.home();
        LCD.print("TLB:"); LCD.print(valueTLB);
        LCD.print(" TRB:"); LCD.print(valueTRB);
        LCD.setCursor(0,1);
        LCD.print("IRB:"); LCD.print(valueIRB);
        LCD.print(" ILB:"); LCD.print(valueILB);
        delay(50);
    }
    delay(250);

    // Intersection Aligners
    while(!startbutton()){
        int valueL = LLRobot::Rel::readQRD(LLRobot::Rel::INL, false);
        int valueR = LLRobot::Rel::readQRD(LLRobot::Rel::INR, false);
        LCD.clear(); LCD.home();
        LCD.print("INL:"); LCD.print(valueL);
        LCD.print(" INR:"); LCD.print(valueR);
        delay(50);
    }
    delay(250);
}

void testQRDs(){
        delay(100);
}
