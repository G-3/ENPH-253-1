#include "EDetect.h"

#include <phys253.h>

#include "LLRobot.h"
#include "EHandler.h"
#include "EDetect.h"
#include "HLRobot.h"
#include "World.h"

#include "Debug.h"

using namespace LLRobot::Rel;

namespace Event{



    EDetect *EDetect::main_instance = 0;
    
    EDetect *EDetect::getInstance(){
        if(!main_instance){
            main_instance = new EDetect;
        }
        return main_instance;
    }

    void EDetect::step(){
        checkIntersect();
        checkBumpers();
        checkIR();
        //checkDropOff();
    }

    bool EDetect::checkIntersect(){
        bool interL = 0;
        bool interR = 0;

        interL = readQRD(IDLF, true);
        interR = readQRD(IDRF, true);	
        
        if(interL || interR) {
            //char msg [100];
            //sprintf(msg, "checkIntersect OK - R: %s L: %s", (interL?"true":"false"), (interR?"true":"false") );
            //Debug::serialPrint(msg, Debug::EDETECT);
            EHandler::intersect(interL, interR);
            return true;
        }
        else{
            //Debug::serialPrint("checkIntersect SKIP - No intersection", Debug::EDETECT);
            return false;
        }
    }

    bool EDetect::checkBumpers(){
        if (readBumper(BF))
            consecutiveBumps+=1;
        else{
            consecutiveBumps = 0;
        }

        if (consecutiveBumps > 5){
            EHandler::collisionDetected(LLRobot::FORWARDS);
            consecutiveBumps = 0;
            return true;
        }
        return false;
    }

    bool EDetect::checkIR(){
        bool eventDetected = false;

        if (timestampIR == 0){
            timestampIR = micros();
        }

        if ((micros()-timestampIR) > IR_TIME_DELAY){
            timestampIR = micros();

            int16_t reading = readCurrentQSD(false);
            switch(irCounter){
                case 0:
                    if ((getPassengerPickup(CL)) || (getPassengerPickup(CR))){
                        if(reading > QRD_THRESH2){
                            EHandler::dropOffDetected(LLRobot::RIGHT);
                            eventDetected = true;
                        }
                    }
                    break;
                case 1:
                    if ((!getPassengerPickup(CL)) || (!getPassengerPickup(CR))){
                        if(reading > QRD_THRESH){
                            EHandler::passengerDetected(LLRobot::RIGHT);
                            eventDetected = true;
                        }
                    }
                    break;
                case 2:
                    if ((getPassengerPickup(CL)) || (getPassengerPickup(CR))){
                        if(reading > QRD_THRESH2){
                            EHandler::dropOffDetected(LLRobot::LEFT);
                            eventDetected = true;
                        }
                    }
                    break;
                case 3:
                    if ((!getPassengerPickup(CL)) || (!getPassengerPickup(CR))){
                        if(reading > QRD_THRESH){
                            EHandler::passengerDetected(LLRobot::LEFT);
                            eventDetected = true;
                        }
                    }
                    break;
            }
            


            //Switch to next qsd 
            irCounter++;
            irCounter %= 4;
            switch(irCounter){
                case 0:
                    setCurrentQSD(IRRU,false);
                    break;
                case 1:
                    setCurrentQSD(IRRM,false);
                    break;
                case 2:
                    setCurrentQSD(IRLU,false);
                    break;
                case 3:
                    setCurrentQSD(IRLM,false);
                    break;
            }
        }
        return eventDetected;
    }

    bool EDetect::checkDropOff(){
        if (getPassengerPickup(CL) || getPassengerPickup(CR)){
            if ((HLRobot::baseNode->id == 13 && HLRobot::lastNode->id == 3)||
                (HLRobot::baseNode->id == 3 && HLRobot::lastNode->id == 13)){
                if (timestampDropOff == 0){
                    timestampDropOff = millis();
                }
                else if(millis() - timestampDropOff > DROP_OFF_TIME){
                    if(HLRobot::baseNode->id == 13){
                        EHandler::dropOffDetected(LLRobot::RIGHT);
                    }else if(HLRobot::baseNode->id == 3) {
                        EHandler::dropOffDetected(LLRobot::LEFT);
                    }
                    timestampDropOff = 0;
                }
            }
        }
    }
}
