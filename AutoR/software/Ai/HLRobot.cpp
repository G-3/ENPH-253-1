#include "HLRobot.h"
#include "World.h"
#include "LLRobot.h"

using namespace LLRobot::Rel;

namespace HLRobot {
    World::Node *lastNode;
    World::Node *baseNode;
    World::Node *destNode;
    OpMode curMode;
   
    bool hasPassenger(){
        return getPassengerPickup(CL) || getPassengerPickup(CR);
    } 

    bool inCircle(){
        bool lastCirc =  (lastNode == World::nodes[8]) || 
                    (lastNode == World::nodes[18]) || 
                    (lastNode == World::nodes[19]);
        bool baseCirc =  (baseNode == World::nodes[8]) || 
                    (baseNode == World::nodes[18]) || 
                    (baseNode == World::nodes[19]);
        return lastCirc && baseCirc;
    }
}
