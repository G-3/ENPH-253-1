#pragma once

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
    
    enum OpMode {TAPE_FOLLOW, INTER_NAV, TRACK_DOWN, GRAB, DROP};

    extern OpMode curMode;

}

