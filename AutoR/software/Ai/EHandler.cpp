#include "EHandler.h"

#include "HLRobot.h"
#include "World.h"
#include "Control/Controller.h"
#include "Control/IntersectNav.h"
#include "Control/TapeFollow.h"
#include "Control/TapeFollow2.h"

#include "Debug.h"

namespace EHandler{
    void intersect(bool left, bool right){                
        // Check to make sure this agrees with our internal model for the base node
         
        // If so start IntersectNavigation
        if (HLRobot::curMode != HLRobot::INTER_NAV){
            HLRobot::curMode = HLRobot::INTER_NAV;
            Debug::serialPrint("EHandler.intersect was called. Swapping to IntersectNav Control Mode.", Debug::EHANDLER);
            Control::Controller::getInstance()->setNextController(new Control::IntersectNav(HLRobot::lastNode, HLRobot::baseNode,HLRobot::destNode));
        }
    }

    void flip(){
        HLRobot::lastNode = HLRobot::baseNode;
        HLRobot::baseNode = HLRobot::lastNode;
        HLRobot::destNode = 0;
    }
   
    void finishIntersect(){
        HLRobot::lastNode = HLRobot::baseNode;
        HLRobot::baseNode = HLRobot::destNode;
        HLRobot::destNode = HLRobot::getNextDest(HLRobot::baseNode);
        Control::Controller::getInstance()->setNextController(new Control::TapeFollow2(126,25,17));
    }

    void falseIntersect(){
         
    }

    void fail(char message[]){
        //LCD.clear(); LCD.home();
        //LCD.print(message);
    }
    
    void finishPickup(){
        if (LLRobot::Rel::getPassengerPickup(LLRobot::Rel::CL) || LLRobot::Rel::getPassengerPickup(LLRobot::Rel::CR)){
            if ((HLRobot::baseNode->id == 13 && HLRobot::lastNode->id == 3)||
                (HLRobot::baseNode->id == 3 && HLRobot::lastNode->id == 13)){
                if(HLRobot::baseNode->id == 13){
                    dropOffDetected(LLRobot::RIGHT);
                }else{
                    dropOffDetected(LLRobot::LEFT);
                }
            }
        Control::Controller::getInstance()->setNextController(new Control::TapeFollow2(126,25,17));
        }
    }

    void finishTurnAround(){
        Control::Controller::getInstance()->setNextController(new Control::TapeFollow2(126,25,17));
        flip();
    }
 
    void finishDropOff(){
        Control::Controller::getInstance()->setNextController(new Control::TapeFollow2(126,25,17));
    }

    void passengerDetected(LLRobot::Side side){

    }
    void collisionDetected(LLRobot::Orientation side){

    }
    void dropOffDetected(LLRobot::Orientation side){

    }
} 
