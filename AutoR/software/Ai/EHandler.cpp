#include <phys253.h>
#include "EHandler.h"
#include "HLRobot.h"
#include "LLRobot.h"
#include "Config.h"
#include "Control/Controller.h"
#include "Control/IntersectSimp.h"
#include "Control/TurnAround.h"
#include "Control/TapeFollow2.h"

#include "Debug.h"

namespace EHandler{
    void intersect(bool left, bool right){                
        // Check to make sure this agrees with our internal model for the base node
         
        // If so start IntersectNavigation
        
        if (HLRobot::curMode != HLRobot::INTER_NAV){
            LCD.clear(); LCD.home(); // LCD.setCursor(0, 1); 
            LCD.print("Inter");LCD.setCursor(0, 1);
            LCD.print(HLRobot::lastNode->id); LCD.print(" ");LCD.print(HLRobot::baseNode->id); LCD.print(" "); LCD.print(HLRobot::destNode->id);
            HLRobot::curMode = HLRobot::INTER_NAV;
           // Debug::serialPrint("EHandler.intersect was called. Swapping to IntersectNav Control Mode.", Debug::EHANDLER);
            Control::Controller::getInstance()->setNextController(new Control::IntersectSimp(HLRobot::lastNode, HLRobot::baseNode,HLRobot::destNode));
        }
    }
 
    void finishIntersect(){
        HLRobot::lastNode = HLRobot::baseNode;
        HLRobot::baseNode = HLRobot::destNode;
        HLRobot::destNode = HLRobot::getNextDest(HLRobot::baseNode);
        LCD.clear(); LCD.home(); // LCD.setCursor(0, 1); 
        LCD.print("Fin");LCD.setCursor(0, 1);
        LCD.print(HLRobot::lastNode->id); LCD.print(" ");LCD.print(HLRobot::baseNode->id); LCD.print(" "); LCD.print(HLRobot::destNode->id);
        if (HLRobot::destNode) { 
            HLRobot::curMode = HLRobot::TAPE_FOLLOW;
            Control::Controller::getInstance()->setNextController(new Control::TapeFollow2(17,25,Config::driveSpeed));
        } else{
            LLRobot::Rel::driveMotors(0,0);
        }
    }

    void falseIntersect(){
         
    }


    void collision(){
        //expected
        //unexpected
        HLRobot::curMode = HLRobot::TURN;
        Control::Controller::getInstance()->setNextController(new Control::TurnAround()); 
        
    }

    void finishTurnAround(){
        //expected
        //if (HLRobot::baseNode->deadEnd){
        flip();
        HLRobot::destNode = HLRobot::getNextDest(HLRobot::baseNode); 
        //}
        //unexpected
        HLRobot::curMode = HLRobot::TAPE_FOLLOW;
        Control::Controller::getInstance()->setNextController(new Control::TapeFollow2(17,25,Config::driveSpeed));
    }
 
    void flip(){
        World::Node *oldLastNode = HLRobot::lastNode;
        HLRobot::lastNode = HLRobot::baseNode;
        HLRobot::baseNode = oldLastNode;
    }
    
    void fail(char message[]){
        //LCD.clear(); LCD.home();
        //LCD.print(message);
    }
    
    void finishPickup(){
        //Control::Controller::getInstance()->setNextController(new Control::TapeFollow());
    }

    void finishDropOff(){
        //Control::Controller::getInstance()->setNextController(new Control::TapeFollow());
    }
} 
