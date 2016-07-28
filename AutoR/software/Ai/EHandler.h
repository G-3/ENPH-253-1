#pragma once

namespace EHandler{
    void intersect(bool left, bool right);
    
    void collision();

    void flip();

    void fail(char message[]);
        
    void finishIntersect();
	
    void falseIntersect();
    
    void finishPickup();

    void finishTurnAround();

    void finishDropOff();
};

