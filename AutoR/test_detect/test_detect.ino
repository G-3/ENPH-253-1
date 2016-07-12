#include <avr/interrupt.h>
#include <LiquidCrystal.h>

#include <phys253.h>

#include "EDetect.h"
#include "LLRobot.h"
#include "Controller.h"

#define ledPin 13

LiquidCrystal LCD(26,27,28,16, 17, 18, 19,20,21,22,23);

motorClass motor ;

ServoTINAH RCServo0;    // declare variables for up to eight     servos.   Replaced old Servo253 implementation 2015Jan2
ServoTINAH RCServo1; 
ServoTINAH RCServo2;

Control::Controller *mainController;

void setup()
{
    #include <phys253setup.txt>
    pinMode(8, OUTPUT);
    mainController = new Control::Controller();
}
 
void loop()
{
    //mainController->step();
    testQRDs();
    
}

void testQRDs(){
    int valueLF = LLRobot::readQRD(LLRobot::TFLF);
    int valueRF = LLRobot::readQRD(LLRobot::TFRF);
    delay(100);
    int valueLB = LLRobot::readQRD(LLRobot::TFLB);
    int valueRB = LLRobot::readQRD(LLRobot::TFRB);
    LCD.clear(); LCD.home();
    LCD.print("LF:"); LCD.print(valueLF);
    LCD.print(" RF:"); LCD.print(valueRF);
    LCD.setCursor(0,1);
    LCD.print("LB:"); LCD.print(valueLB);
    LCD.print(" RB:"); LCD.print(valueRB);
    delay(100);
}
