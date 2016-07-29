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

LiquidCrystal LCD(26,27,28,16, 17, 18, 19,20,21,22,23);

motorClass motor ;

ServoTINAH RCServo0;    // declare variables for up to eight     servos.   Replaced old Servo253 implementation 2015Jan2
ServoTINAH RCServo1; 
ServoTINAH RCServo2;
ServoTINAH RCServo3;

uint8_t ultimateLast = 13;
uint8_t ultimateBase = 3;

void setup_m()
{
    #include <phys253setup.txt>
    Serial.begin(9600);
    
    World::setup(); 
    LLRobot::initialize(); 
    LCD.clear(); LCD.home();
    LCD.print("Persist");
    LCD.print(ultimateLast);
    delay(500);

    HLRobot::pathCounter = 0;
    HLRobot::lastNode = World::nodes[1];
    HLRobot::baseNode = World::nodes[2];
    World::updatePath(HLRobot::baseNode->id, ultimateLast); 
    Serial.println(HLRobot::path[0]->id);    
    Serial.println(HLRobot::path[1]->id);    
    Serial.println(HLRobot::path[2]->id);    
    HLRobot::destNode = HLRobot::getNextDest(HLRobot::baseNode);
    Serial.println(HLRobot::destNode->id);    
}
int counter = 0;

void loop_m()
{
    counter += 1;
    if(counter%20 == 0){
        counter = 0;
        if(stopbutton()){
            HLRobot::pathCounter = 0;
            HLRobot::lastNode = World::nodes[0];
            HLRobot::baseNode = World::nodes[1];
            World::updatePath(HLRobot::baseNode->id, ultimateLast); 
            HLRobot::destNode = HLRobot::getNextDest(HLRobot::baseNode);
            HLRobot::curMode = HLRobot::TAPE_FOLLOW;
            Control::Controller::getInstance()->setNextController(new Control::TapeFollow2(17,25,100));
            delay(250);
        }
    }
    //Serial.println("Testing1");    
    //Serial.println(HLRobot::destNode->id);    
    if (HLRobot::baseNode == World::nodes[ultimateLast]){
        HLRobot::destNode = World::nodes[ultimateBase];   
    }
    if( !HLRobot::destNode){ //&& (HLRobot::baseNode->id != ultimateLast) ){
        World::updatePath(HLRobot::baseNode->id, ultimateLast); 
        HLRobot::destNode = HLRobot::getNextDest(HLRobot::baseNode);
    }
    
    //Serial.println("Testing2");    
    //Serial.println(HLRobot::destNode->id);    
    Event::EDetect::getInstance()->step();
    if (HLRobot::baseNode == World::nodes[ultimateLast]){
        HLRobot::destNode = World::nodes[ultimateBase];   
    }
    if( !HLRobot::destNode){ // && (HLRobot::baseNode->id != ultimateLast) ){
        World::updatePath(HLRobot::baseNode->id, ultimateLast); 
        HLRobot::destNode = HLRobot::getNextDest(HLRobot::baseNode);
    }   
    //Serial.println("Testing3");    
    //Serial.println(HLRobot::destNode->id);    
    Control::Controller::getInstance()->step();
    //Serial.println("Testing4");    
    //Serial.println(HLRobot::destNode->id);    
    //delay(100);
    //testQRDs();
}
