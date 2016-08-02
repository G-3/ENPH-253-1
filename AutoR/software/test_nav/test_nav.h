#include <avr/interrupt.h>
#include <LiquidCrystal.h>

#include <phys253.h>

#include "../Ai/Debug.h"

#include "../Ai/World.h"
#include "../Ai/EDetect.h"
#include "../Ai/LLRobot.h"
#include "../Ai/Control/Controller.h"
#include "../Ai/Control/TapeFollow2.h"
#include "../Ai/HLRobot.h"

#define ledPin 13

LiquidCrystal LCD(26,27,28,16, 17, 18, 19,20,21,22,23);

motorClass motor ;

ServoTINAH RCServo0;    // declare variables for up to eight     servos.   Replaced old Servo253 implementation 2015Jan2
ServoTINAH RCServo1; 
ServoTINAH RCServo2;
ServoTINAH RCServo3;

uint8_t start=11; 
uint8_t base=12; 
uint8_t end=13; 


void setup_m()
{

    #include <phys253setup.txt>
    Serial.begin(9600);
   
    pinMode(8, OUTPUT);
    
    Debug::serialPrint("Initialized. Starting up.", Debug::GENERAL); 
 
    LCD.clear(); LCD.home();
    LCD.print("Starting up...3");
    delay(500);
    
    World::setup();
       LCD.clear(); LCD.home();
    LCD.print("Starting up...2");
    delay(500);
    
    LCD.clear(); LCD.home();
    LCD.print("Starting up...1");
    delay(500);
/*    
    uint8_t choose = knob(7)/16;
    while(!stopbutton()){
        choose = knob(7)/40;
        LCD.clear(); LCD.home();
        LCD.print("Start:"); LCD.print(choose);
        LCD.setCursor(0, 1);
        LCD.print("Prev:"); LCD.print(start); 
        delay(20);
    }
    start = choose;
    delay(250);

    while(!stopbutton()){
        choose = knob(7)/40;
        LCD.clear(); LCD.home();
        LCD.print("Base:"); LCD.print(choose);
        LCD.setCursor(0, 1);
        LCD.print("Prev:"); LCD.print(base); 
    }
    base = choose;
    delay(250);

    while(!stopbutton()){
        choose = knob(7)/40;
        LCD.clear(); LCD.home();
        LCD.print("End:"); LCD.print(choose);
        LCD.setCursor(0, 1);
        LCD.print("Prev:"); LCD.print(end); 
    }
    end = choose;
    delay(250);
  */  HLRobot::lastNode = World::nodes[start];
    HLRobot::baseNode = World::nodes[base];
    HLRobot::destNode = World::nodes[end];
}
 
unsigned long starttime = 0;
unsigned long endtime = 0;

unsigned int counter = 0;

void loop_m()
{
    counter += 1;
    HLRobot::lastNode = World::nodes[start];
    HLRobot::baseNode = World::nodes[base];
    HLRobot::destNode = World::nodes[end];

//    starttime = micros();
//    analogRead(4); 
//    endtime = micros();
//    starttime = micros();
    //LLRobot::Rel::readQRD(LLRobot::Rel::IDLF, true);
    Event::EDetect::getInstance()->step();
    Control::Controller::getInstance()->step();
//    endtime = micros();
//    Serial.print("Time: "); Serial.println(endtime - starttime);
    //testQRDs();
    if(!(counter % 100)){
        //int interR = LLRobot::Rel::readQRD(LLRobot::Rel::IDRF, false);
        //int interL = LLRobot::Rel::readQRD(LLRobot::Rel::IDLF, false);
        //Serial.print("L: "); Serial.println(interL);
        //Serial.print("R: "); Serial.println(interR);
        if(startbutton()){
            HLRobot::curMode = HLRobot::TAPE_FOLLOW;
            Control::Controller::getInstance()->setNextController(new Control::TapeFollow2(17,25,100));
        }
        if(stopbutton()){
            delay(250);
            uint8_t choose = knob(7)/16;
            while(!startbutton()){
                choose = knob(7)/40;
                LCD.clear(); LCD.home();
                LCD.print("Start:"); LCD.print(choose);
                LCD.setCursor(0, 1);
                LCD.print("Prev:"); LCD.print(start); 
                delay(20);
            }
            start = choose;
            delay(250);

            while(!startbutton()){
                choose = knob(7)/16;
                LCD.clear(); LCD.home();
                LCD.print("Base:"); LCD.print(choose);
                LCD.setCursor(0, 1);
                LCD.print("Prev:"); LCD.print(base); 
                delay(20);
            }
            base = choose;
            delay(250);

            while(!startbutton()){
                choose = knob(7)/16;
                LCD.clear(); LCD.home();
                LCD.print("End:"); LCD.print(choose);
                LCD.setCursor(0, 1);
                LCD.print("Prev:"); LCD.print(end); 
                delay(20);
            }
            end = choose;
            delay(250);
            
            HLRobot::curMode = HLRobot::TAPE_FOLLOW;
            Control::Controller::getInstance()->setNextController(new Control::TapeFollow2(17,25,100));
        }
        counter = 0;
    }
}
