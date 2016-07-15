#include "EDetect.h"
#include "LLRobot.h"

namespace Event{
    void EDetect::step(){
	count+=1;
	if(count%2==0){
            checkIntersect();
	}
    }

    void checkIntersect(bool dir){
        int interL = 0;
        int interR = 0;
        if(dir){
            interL = LLRobot::Rel::readQRD(LLRobot::Rel::IDLF, true);
            interR = LLRobot::Rel::readQRD(LLRobot::Rel::IDRF, true);	
        } 
        else{
            interL = LLRobot::Rel::readQRD(LLRobot::Rel::IDLB, true);
            interR = LLRobot::Rel::readQRD(LLRobot::Rel::IDRB, true);	
        }

        if(interL || interR) {}
    }
}

