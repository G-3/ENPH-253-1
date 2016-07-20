#include "test_llrobot.h"

#include <avr/interrupt.h>

#include "../Ai/Debug.h"
#include "../Ai/LLRobot.h"

LiquidCrystal LCD(26,27,28,16,17,18,19,20,21,22,23);

motorClass motor;

ServoTINAH RCServo0;    // declare variables for up to eight     servos.   Replaced old Servo253 implementation 2015Jan2
ServoTINAH RCServo1; 
ServoTINAH RCServo2;
ServoTINAH RCServo3;

using namespace LLRobot;

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
    LCD.clear(); LCD.home();
    LCD.print("Done!");
    delay(200);
}
bool setOrientation(){
    while(!startbutton){
        LCD.clear();
        LCD.home();
        LCD.print("Current Orientation");
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
}


void testQRD(){
    Orientation orientation = FORWARDS;
    while(!startbutton()){
        if (orientation == FORWARDS){
            if (stopbutton()){
                flip();
                while(stopbutton());
            }
        }
    }
}

void testQSD(){
    bool side = true;
    while(!startbutton()){

    }

}

void testTripSensors(){

}

void testArms(){

}
void testClaws(){

}
