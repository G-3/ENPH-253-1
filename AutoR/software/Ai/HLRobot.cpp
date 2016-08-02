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
}
