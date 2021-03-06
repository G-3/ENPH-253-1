#pragma once

#include "Config.h"

namespace World {
	class Node;
}

namespace HLRobot{
    // The node we came from for direction purposes. 
    // After navigating the baseNode the baseNode will be the lastNode. 
    // In case of reversing before a node, this will flip with destNode
    extern World::Node *lastNode;

    // The node that we are on the edge towards and need to navigate. 
    // After navigating it this becomes the lastNode.
    extern World::Node *baseNode;
    
    // The node that we need to navigate towards next. 
    // After the baseNode is navigated, this becomes the new basenode.
    extern World::Node *destNode;

    enum OpMode {TAPE_FOLLOW = 0, INTER_NAV = 1, PICKUP = 2, DROP_OFF = 3, TURN_AROUND = 4, IDLE = 5};
    
    extern OpMode curMode;

    /*
     * Checks if we are currently carrying a passenger.
     */
    bool hasPassenger();
}

