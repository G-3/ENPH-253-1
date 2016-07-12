#ifndef __EDETECT_H_INCLUDED__
#define __EDETECT_H_INCLUDED__

#include "LLRobot.h"


namespace Event{
    class EDetect{
	private:
	    EDetect(){};
	    int count = 0;
	public:
	    void step();
    };

    void checkIntersect();
};
#endif // __EDETECT_H_INCLUDED__ 
