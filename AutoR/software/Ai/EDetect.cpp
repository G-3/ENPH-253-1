#include "EDetect.h"

#include <phys253.h>

#include "LLRobot.h"
#include "EHandler.h"
#include "EDetect.h"

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
        count+=1;
        //if(count%2==0){
                checkIntersect();
        //}
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
            consecutiveBumps++;
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

            switch(irCounter){
                case 0:
                    if(readCurrentQSD(false) > 200){
                        EHandler::passengerDetected(LLRobot::RIGHT);
                        eventDetected = true;
                    }

                    break;
                case 1:
                    if(readCurrentQSD(false) > 200){
                        EHandler::passengerDetected(LLRobot::LEFT);
                        eventDetected = true;
                    }
                    break;
                case 2:
                    if(readCurrentQSD(false) > 700){
                        EHandler::dropOffDetected(LLRobot::RIGHT);
                        eventDetected = true;
                    }
                    break;
                case 3:
                    if(readCurrentQSD(false) > 700){
                        EHandler::dropOffDetected(LLRobot::LEFT);
                        eventDetected = true;
                    }
                    break;
            }


            //Switch to next Event
            irCounter++;
            irCounter %= 4;
            switch(irCounter){
                case 0:
                    setCurrentQSD(IRRM,false);
                    break;
                case 1:
                    setCurrentQSD(IRLM,false);
                    break;
                case 2:
                    setCurrentQSD(IRRU,false);
                    break;
                case 3:
                    setCurrentQSD(IRLU,false);
                    break;
            }
            
        }
        return eventDetected;
    }
}

