#pragma once

#include "LLRobot.h"
namespace EHandler{
    void intersect(bool left, bool right);
    
    void collision();

    void flip();

    void fail(char message[]);
        
    void finishIntersect();
	
    void falseIntersect();
    
    void passengerDetected(LLRobot::Side side);
    void collisionDetected(LLRobot::Orientation side);
    void dropOffDetected(LLRobot::Side side);
    void finishPickup();

    void finishTurnAround();

    void finishDropOff();
};

