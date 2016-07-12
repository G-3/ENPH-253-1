#include "Ai/EDetect.h"
#include "Ai/LLRobot.h"

namespace Event{
    void EDetect::step(){
	count+=1;
	if(count%2==0){
		 
	}
    }
    
    namespace Intersect{

        void checkIntersect(bool dir){
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
}

