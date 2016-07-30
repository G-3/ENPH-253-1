#include <avr/interrupt.h>
#include <LiquidCrystal.h>

#include <phys253.h>
#include "../Ai/Debug.h"
#include "../Ai/LLRobot.h"
#include "../Ai/Control/TapeFollow2.h"

#define ledPin 13

LiquidCrystal LCD(26,27,28,16, 17, 18, 19,20,21,22,23);

motorClass motor ;

ServoTINAH RCServo0;    // declare variables for up to eight     servos.   Replaced old Servo253 implementation 2015Jan2
ServoTINAH RCServo1; 
ServoTINAH RCServo2;
ServoTINAH RCServo3;

using namespace LLRobot;

void setup_m(){
    #include <phys253setup.txt>
    Serial.begin(9600);
   
    initialize();
    
    Debug::serialPrint("Initialized. Starting up.", Debug::GENERAL); 
 
    LCD.clear(); LCD.home();
    LCD.print("Starting up...");
    delay(50);
}
 
void loop_m();

void loop_m(){
    int16_t base = 0;
    int16_t dGain = 0;
    int16_t pGain = 0;
    int16_t eGain = 0;
    int16_t eBase = 0;
    int16_t hysteresis = 0;
    Control::TapeFollow2* tf = new Control::TapeFollow2(base,dGain,pGain);
    while(true){
        if (stopbutton()){
            int16_t val;
            while(!startbutton()){
                delay(100);
                LCD.clear();
                LCD.setCursor(0,0);
                LCD.print("Base:");
                val = knob(6)/4;
                LCD.print(val);
                LCD.setCursor(0,1);
                LCD.print("Prev:");
                LCD.print(base);
                
            }
            base = val;
            while(startbutton());

            while(!startbutton()){
                delay(100);
                LCD.clear();
                LCD.setCursor(0,0);
                LCD.print("D Gain:");
                val = knob(6)/16;
                LCD.print(val);
                LCD.setCursor(0,1);
                LCD.print("Prev:");
                LCD.print(dGain);
                
            }
            dGain = val;
            while(startbutton());

            while(!startbutton()){
                delay(100);
                LCD.clear();
                LCD.setCursor(0,0);
                LCD.print("P Gain:");
                val = knob(6)/16;
                LCD.print(val);
                LCD.setCursor(0,1);
                LCD.print("Prev:");
                LCD.print(pGain);
                
            }
            pGain = val;
            while(startbutton());

            while(!startbutton()){
                delay(100);
                LCD.clear();
                LCD.setCursor(0,0);
                LCD.print("E Base:");
                val = knob(6)/16;
                LCD.print(val);
                LCD.setCursor(0,1);
                LCD.print("Prev:");
                LCD.print(eBase);
                
            }
            eBase = val;

            while(startbutton());
            while(!startbutton()){
                delay(100);
                LCD.clear();
                LCD.setCursor(0,0);
                LCD.print("E Gain:");
                val = knob(6)/16;
                LCD.print(val);
                LCD.setCursor(0,1);
                LCD.print("Prev:");
                LCD.print(eGain);
                
            }
            eGain = val;
            while(startbutton());

            while(!startbutton()){
                delay(100);
                LCD.clear();
                LCD.setCursor(0,0);
                LCD.print("Hyst:");
                val = knob(6)/16;
                LCD.print(val);
                LCD.setCursor(0,1);
                LCD.print("Prev:");
                LCD.print(hysteresis);
                
            }
            hysteresis = val;
            while(startbutton());

            delete tf;
            tf = new Control::TapeFollow2(dGain,pGain,base,eBase,eGain,hysteresis);

            LCD.clear();
            LCD.print("Following tape");
        }

        tf->step();
        delay(1);

    }

    

}

