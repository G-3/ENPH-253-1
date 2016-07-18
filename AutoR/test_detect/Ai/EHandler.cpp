#include "EHandler.h"

#include "HLRobot.h"
#include "Control/Controller.h"
#include "Control/IntersectNav.h"

#include "Debug.h"

namespace EHandler{
    void intersect(bool left, bool right){                
        // Check to make sure this agrees with our internal model for the base node
        
           
        // If so start IntersectNavigation
        if (HLRobot::curMode != HLRobot::INTER_NAV){
            HLRobot::curMode = HLRobot::INTER_NAV;
            Debug::serialPrint("EHandler.intersect was called. Swapping to IntersectNav Control Mode.", Debug::EHANDLER);
            Control::Controller::getInstance()->swapController(new Control::IntersectNav(HLRobot::lastNode, HLRobot::baseNode,HLRobot::destNode));    
        }
    }
    
    void falseIntersect(){
         
    }

    void fail(char message[]){
        //LCD.clear(); LCD.home();
        //LCD.print(message);
    }

} 
