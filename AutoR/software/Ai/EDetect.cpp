#include "EDetect.h"

#include <phys253.h>

#include "LLRobot.h"
#include "EHandler.h"

#include "Debug.h"

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
        if(count%2==0){
                checkIntersect();
        }
    }

    bool checkIntersect(){
        bool interL = 0;
        bool interR = 0;

        interL = LLRobot::Rel::readQRD(LLRobot::Rel::IDLF, true);
        interR = LLRobot::Rel::readQRD(LLRobot::Rel::IDRF, true);	
        
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
}

