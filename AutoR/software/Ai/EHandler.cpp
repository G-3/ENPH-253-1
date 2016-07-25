#include "EHandler.h"

#include "HLRobot.h"
#include "Control/Controller.h"
#include "Control/IntersectNav.h"
#include "Control/TapeFollow.h"

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
        HLRobot::destNode = HLRobot::path[1];
        Control::Controller::getInstance()->setNextController(new Control::TapeFollow());
    }

    void falseIntersect(){
         
    }

    void fail(char message[]){
        //LCD.clear(); LCD.home();
        //LCD.print(message);
    }
    
    void finishPickup(){
        Control::Controller::getInstance()->setNextController(new Control::TapeFollow());
    }

    void finishTurnAround(){
        Control::Controller::getInstance()->setNextController(new Control::TapeFollow());
    }
 
    void finishDropOff(){
        Control::Controller::getInstance()->setNextController(new Control::TapeFollow());
    }
} 
