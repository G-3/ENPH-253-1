#include "EDetect.h"

#include <phys253.h>

#include "LLRobot.h"
#include "EHandler.h"

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
        if(count%2==0){
                checkIntersect();
        }
    }

    void checkIntersect(){
        bool interL = 0;
        bool interR = 0;

        interL = readQRD(IDLF, true);
        interR = readQRD(IDRF, true);	
        
        if(interL || interR) {
            char msg [100];
            sprintf(msg, "checkIntersect OK - R: %s L: %s", (interL?"true":"false"), (interR?"true":"false") );
            Debug::serialPrint(msg, Debug::EDETECT);
            EHandler::intersect(interL, interR);
        }
        else{
            Debug::serialPrint("checkIntersect SKIP - No intersection", Debug::EDETECT);
        }
    }

    void checkBumper(){
        
    }
    void checkIR(){
        if (timestamp == 0){
            timestamp = micros();
        }

        if ((micros()-timestamp) > IR_TIME_DELAY){
            timestamp = micros();
            slowDownCounter++;
            slowDownCounter %= slowDownFactor;
            if (slowDownCounter == 0){
                fCounter++;
                fCounter %= F_LENGHT;
                
            }
            else{
                sCounter++;
                sCounter %+ S_LENGHT; 

            }
            

        }


    }
}

