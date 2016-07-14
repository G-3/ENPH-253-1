#include <avr/interrupt.h>
#include <LiquidCrystal.h>

#include <phys253.h>

#include "Ai/EDetect.h"
#include "Ai/LLRobot.h"
#include "Ai/Control/Controller.h"

#define ledPin 13

LiquidCrystal LCD(26,27,28,16, 17, 18, 19,20,21,22,23);

motorClass motor ;

ServoTINAH RCServo0;    // declare variables for up to eight     servos.   Replaced old Servo253 implementation 2015Jan2
ServoTINAH RCServo1; 
ServoTINAH RCServo2;
ServoTINAH RCServo3;

Control::Controller *mainController;

void setup()
{
    #include <phys253setup.txt>
    Serial.begin(9600);
    
    pinMode(8, OUTPUT);
    
    Serial.println("Test");
    
    LCD.clear(); LCD.home();
    LCD.print("Starting up...3");
    delay(1000);
    
    Serial.println("Starting"); 
    LCD.clear(); LCD.home();
    LCD.print("Starting up...2");
    delay(1000);
    
    Serial.println("Starting");
    LCD.clear(); LCD.home();
    LCD.print("Starting up...1");
    delay(1000);
    
    mainController = new Control::Controller();
}
 
void loop()
{
    Serial.println("Starting");
    mainController->step();
    //testQRDs();
}

void testQRDs(){
    int valueLF = LLRobot::readQRD(LLRobot::TFLF, false);
    int valueRF = LLRobot::readQRD(LLRobot::TFRF, false);
    delay(100);
    int valueLB = LLRobot::readQRD(LLRobot::TFLB, false);
    int valueRB = LLRobot::readQRD(LLRobot::TFRB, false);
    LCD.clear(); LCD.home();
    LCD.print("LF:"); LCD.print(valueLF);
    LCD.print(" RF:"); LCD.print(valueRF);
    LCD.setCursor(0,1);
    LCD.print("LB:"); LCD.print(valueLB);
    LCD.print(" RB:"); LCD.print(valueRB);
    delay(100);
}
