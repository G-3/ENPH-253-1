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
            interL = LLRobot::readQRD(LLRobot::IDLF, true);
            interR = LLRobot::readQRD(LLRobot::IDRF, true);	
        } else{
            interL = LLRobot::readQRD(LLRobot::IDLB, true);
            interR = LLRobot::readQRD(LLRobot::IDRB, true);	
        }

        if(interL || interR) {}
    }
}

