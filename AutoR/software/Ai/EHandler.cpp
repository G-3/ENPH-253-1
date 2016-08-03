#include <phys253.h>
#include "EHandler.h"
#include "HLRobot.h"
#include "World.h"
#include "LLRobot.h"
#include "Config.h"
#include "PathPlan/Planner.h"
#include "Control/Controller.h"
#include "Control/Idle.h"
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
        // If so start IntersectNavigation
        
        switch(curMode){
            case TAPE_FOLLOW:
                LLRobot::Rel::driveMotors(-20,-20); 
                delay(5);
                // TODO: Check to make sure left right agrees with our internal model for the base node
                PathPlan::Planner::getInstance()->update();
                if (destNode == 0) {
                    // If we have no more destination to turn towards in this intersection, stall
                    curMode = IDLE;
                    Control::Controller::getInstance()->setNextController(new Control::Idle());
                    /*
                    LCD.clear(); 
                    LCD.home(); 
                    LCD.print("I'm done");LCD.setCursor(0, 1);
                    LCD.print(lastNode->id); LCD.print(" ");LCD.print(baseNode->id); LCD.print(" "); LCD.print(destNode->id);
                */
                }
                else if(destNode == lastNode){
                    // We actually want to be turning around
                    curMode = TURN_AROUND;
                    Control::Controller::getInstance()->setNextController(new Control::TurnAround());
                }
                else{
                    // Otherwise navigate the intersection
                    curMode = INTER_NAV;
                    Control::Controller::getInstance()->setNextController(new Control::IntersectSimp(lastNode, baseNode,destNode));

                    LCD.clear(); LCD.home(); 
                    LCD.print("Inter");LCD.setCursor(0, 1);
                    LCD.print(lastNode->id); LCD.print(" ");LCD.print(baseNode->id); LCD.print(" "); LCD.print(destNode->id);
                }
                break;
        }
    }
 
    void finishIntersect(){
        PathPlan::Planner::getInstance()->finishedIntersect();
        /*
        LCD.clear(); LCD.home();  
        LCD.print("FInter");LCD.setCursor(0, 1);
        LCD.print(lastNode->id); LCD.print(" ");LCD.print(baseNode->id); LCD.print(" "); 
        if(destNode){
            LCD.print(destNode->id);
        }*/
        
        //if (baseNode){
        curMode = TAPE_FOLLOW;
        Control::Controller::getInstance()->setNextController(new Control::TapeFollow2(17,25,Config::driveSpeed));
        //}
        //else {
            // This should never happen
        //    LCD.clear(); LCD.home(); 
        //    LCD.print("NO BASE");LCD.setCursor(0, 1);
        //    LCD.print(lastNode->id);
        //    delay(100000); 
        //}
    }

    void falseIntersect(){
         
    }

    void finishTurnAround(){
        PathPlan::Planner::getInstance()->finishedTurnAround();
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
        PathPlan::Planner::getInstance()->finishedPickUp();
        curMode = TAPE_FOLLOW;
        Control::Controller::getInstance()->setNextController(new Control::TapeFollow2(17,25,Config::driveSpeed));
    }
 
    void finishDropOff(){
        PathPlan::Planner::getInstance()->finishedDropOff();
        curMode = TAPE_FOLLOW;
        Control::Controller::getInstance()->setNextController(new Control::TapeFollow2(17,25,Config::driveSpeed));
    }

    void passengerDetected(LLRobot::Side side){
        //Serial.println("Mode: ");
        //Serial.println((int)curMode);
        switch(curMode){
            case TAPE_FOLLOW:
                curMode = PICKUP;
                Control::Controller::getInstance()->setNextController(new Control::Pickup(side));
        }
    }
    void collisionDetected(LLRobot::Orientation side){
        switch(curMode){
            case TAPE_FOLLOW:
                LCD.clear(); LCD.home();
                LCD.print("COLLISION"); 
                LLRobot::Rel::driveMotors(-20,-20); 
                delay(100);
                curMode = TURN_AROUND;
                Control::Controller::getInstance()->setNextController(new Control::TurnAround());
        }
    }
    void dropOffDetected(LLRobot::Side side){
        switch(curMode){
            case TAPE_FOLLOW:
                curMode = DROP_OFF;
                Control::Controller::getInstance()->setNextController(new Control::DropOff(side));
        }
    }
} 
