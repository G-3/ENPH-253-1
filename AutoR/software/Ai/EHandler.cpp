#include <phys253.h>
#include "EHandler.h"
#include "HLRobot.h"
#include "World.h"
#include "LLRobot.h"
#include "Config.h"
#include "Control/Controller.h"
#include "Control/Pickup.h"
#include "Control/IntersectNav.h"
#include "Control/IntersectSimp.h"
#include "Control/TurnAround.h"
#include "Control/TapeFollow2.h"
#include "Control/TurnAround.h"
#include "Control/DropOff.h"

#include "Debug.h"

using namespace HLRobot;

namespace EHandler{
    void intersect(bool left, bool right){                
        switch(curMode){
            case TAPE_FOLLOW:
                LCD.clear(); LCD.home(); // LCD.setCursor(0, 1); 
                LCD.print("Inter");LCD.setCursor(0, 1);
                LCD.print(lastNode->id); LCD.print(" ");LCD.print(baseNode->id); LCD.print(" "); LCD.print(destNode->id);
                curMode = INTER_NAV;
               // Debug::serialPrint("EHandler.intersect was called. Swapping to IntersectNav Control Mode.", Debug::EHANDLER);
                Control::Controller::getInstance()->setNextController(new Control::IntersectSimp(lastNode, baseNode,destNode));

        }
    }
 
    void finishIntersect(){
        lastNode = baseNode;
        baseNode = destNode;
        destNode = getNextDest(baseNode);
        if (destNode) { 
            curMode = TAPE_FOLLOW;
            Control::Controller::getInstance()->setNextController(new Control::TapeFollow2(17,25,Config::driveSpeed));
        } else{
            LLRobot::Rel::driveMotors(0,0);
        }
    }

    void falseIntersect(){
         
    }

    void finishTurnAround(){
        //expected
        //if (HLRobot::baseNode->deadEnd){
        flip();
        destNode = getNextDest(baseNode); 
        //}
        //unexpected
        curMode = TAPE_FOLLOW;
        Control::Controller::getInstance()->setNextController(new Control::TapeFollow2(17,25,Config::driveSpeed));
    }
 
    void flip(){
        World::Node *oldLastNode = lastNode;
        lastNode = baseNode;
        baseNode = oldLastNode;
    }
    
    void fail(char message[]){
        //LCD.clear(); LCD.home();
        //LCD.print(message);
    }
    
    void finishPickup(){
        Serial.println("Finishing Pickup");
        if (LLRobot::Rel::getPassengerPickup(LLRobot::Rel::CL) || LLRobot::Rel::getPassengerPickup(LLRobot::Rel::CR)){
            if ((baseNode->id == 13 && lastNode->id == 3)||
                (baseNode->id == 3 && lastNode->id == 13)){
                if(baseNode->id == 13){
                    dropOffDetected(LLRobot::RIGHT);
                }else{
                    dropOffDetected(LLRobot::LEFT);
                }
            }
        curMode = TAPE_FOLLOW;
        Control::Controller::getInstance()->setNextController(new Control::TapeFollow2(17,25,Config::driveSpeed));
        }
    }
 
    void finishDropOff(){
        Serial.println("Finishing DropOff");
        curMode = TAPE_FOLLOW;
        Control::Controller::getInstance()->setNextController(new Control::TapeFollow2(17,25,Config::driveSpeed));
    }

    void passengerDetected(LLRobot::Side side){
        switch(curMode){
            case TAPE_FOLLOW:
                curMode = PICKUP;
                Control::Controller::getInstance()->setNextController(new Control::Pickup(side));
        }
    }
    void collisionDetected(LLRobot::Orientation side){
        switch(curMode){
            case TAPE_FOLLOW:
                curMode = TURN_AROUND;
                Control::Controller::getInstance()->setNextController(new Control::TurnAround());
        }
    }
    void dropOffDetected(LLRobot::Side side){
        switch(curMode){
            case TAPE_FOLLOW:
                Serial.println("DropOff Detected");
                curMode = DROP_OFF;
                Control::Controller::getInstance()->setNextController(new Control::DropOff(side));
        }
    }
} 
