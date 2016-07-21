#pragma once

#include "LLRobot.h"
namespace EHandler{
    void intersect(bool left, bool right);

    void finishIntersect();
	
    void falseIntersect();

    void passengerDetected(LLRobot::Side side);
    void collisionDetected(LLRobot::Orientation side);
    void dropOffDetected(LLRobot::Orientation side);


};

