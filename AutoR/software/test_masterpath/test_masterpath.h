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

uint8_t masterPath[14] = {3, 4, 5, 6, 5, 7, 5, 4, 1, 0, 1, 2, 3, 13};
//{13, 14, 15, 17, 15, 16 , 15, 14, 11}; 
//{10,11,12,13};
uint8_t masterPathSize = 14;
//9;
//4; 


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
    
    //Serial.println(World::nodes[11]->linked[0]->id); Serial.println(World::nodes[11]->linked[1]->id); Serial.println(World::nodes[11]->linked[2]->id);Serial.println(World::nodes[11]->linked[3]->id); 
    //Serial.println();
    //Serial.println(World::nodes[5]->linked[0]->id); Serial.println(World::nodes[5]->linked[1]->id); Serial.println(World::nodes[5]->linked[2]->id);Serial.println(World::nodes[5]->linked[3]->id); 
    LCD.clear(); LCD.home();
    LCD.print("Starting up...1");
    delay(500);

    HLRobot::pathCounter = 0;
    HLRobot::lastNode = World::nodes[masterPath[0]];
    HLRobot::baseNode = World::nodes[masterPath[1]];
    for (int i = 1; i < masterPathSize; i++){
        HLRobot::path[i-1] = World::nodes[masterPath[i]];
    }
    HLRobot::path[masterPathSize-1] = 0;
    HLRobot::destNode = HLRobot::getNextDest(HLRobot::baseNode);
}
int counter = 0;

void loop_m()
{
    counter += 1;
    if(counter%20 == 0){
        counter = 0;
        if(stopbutton()){
            
            HLRobot::pathCounter = 0;
            HLRobot::lastNode = World::nodes[masterPath[0]];
            HLRobot::baseNode = World::nodes[masterPath[1]];
            for (int i = 1; i < masterPathSize; i++){
                HLRobot::path[i-1] = World::nodes[masterPath[i]];
            }
            HLRobot::path[masterPathSize-1] = 0;
            HLRobot::destNode = HLRobot::getNextDest(HLRobot::baseNode);
            //Serial.print(HLRobot::lastNode->id); Serial.print(" ");Serial.print(HLRobot::baseNode->id); Serial.print(" "); Serial.println(HLRobot::destNode->id);
            
            //World::Dir destDir = HLRobot::baseNode->relDestDir(HLRobot::destNode, HLRobot::lastNode);
           /* 
            World::Dir destDir = World::nodes[11]->relDestDir(World::nodes[12], World::nodes[10]);
            Serial.print("DestDir"); Serial.println((int)destDir); Serial.println(destDir);
            Serial.println(World::nodes[11]->linked[0]->id); Serial.println(World::nodes[11]->linked[1]->id); Serial.println(World::nodes[11]->linked[2]->id);Serial.println(World::nodes[11]->linked[3]->id); 
            */
            HLRobot::curMode = HLRobot::TAPE_FOLLOW;
            Control::Controller::getInstance()->setNextController(new Control::TapeFollow2(17,25,100));
            delay(250);
        }
    }
    Event::EDetect::getInstance()->step();
    Control::Controller::getInstance()->step();
    //testQRDs();
}
