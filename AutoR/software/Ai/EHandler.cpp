#include "EHandler.h"

#include "HLRobot.h"
#include "Control/Controller.h"
#include "Control/Pickup.h"
#include "Control/IntersectNav.h"
#include "Control/TapeFollow2.h"
#include "Control/TurnAround.h"

#include "Debug.h"

using namespace HLRobot;

namespace EHandler{
    void intersect(bool left, bool right){                
        // Check to make sure this agrees with our internal model for the base node
         
        // If so start IntersectNavigation
        if (curMode != INTER_NAV){
            curMode = INTER_NAV;
            Debug::serialPrint("EHandler.intersect was called. Swapping to IntersectNav Control Mode.", Debug::EHANDLER);
            Control::Controller::getInstance()->setNextController(new Control::IntersectNav(lastNode, baseNode,destNode));
        }
    }

    void flip(){
        lastNode = baseNode;
        baseNode = lastNode;
        destNode = 0;
    }
   
    void finishIntersect(){
        lastNode = baseNode;
        baseNode = destNode;
        destNode = getNextDest(baseNode);
        Control::Controller::getInstance()->setNextController(new Control::TapeFollow2(126,25,17));
    }

    void falseIntersect(){
         
    }

    void fail(char message[]){
        //LCD.clear(); LCD.home();
        //LCD.print(message);
    }
    
    void finishPickup(){
        Control::Controller::getInstance()->setNextController(new Control::TapeFollow2(126,25,17));
    }

    void finishTurnAround(){
        Control::Controller::getInstance()->setNextController(new Control::TapeFollow2(126,25,17));
        flip();
    }
 
    void finishDropOff(){
        Control::Controller::getInstance()->setNextController(new Control::TapeFollow2(126,25,17));
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
            case TURN_AROUND:
            case INTER_NAV:
            case PICKUP:
                break;
            default:
                Control::Controller::getInstance()->setNextController(new Control::TurnAround());
        }
    }
    void dropOffDetected(LLRobot::Orientation side){
    }
} 
