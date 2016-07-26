#include "HLRobot.h"
#include "World.h"

namespace HLRobot {
    World::Node *lastNode;
    World::Node *baseNode;
    World::Node *destNode;
    World::Node *path[Config::linksSize] = {};

    World::Node *getNextDest(World::Node* base){
        uint8_t i = 0;
        World::Node *nextDest = 0;
        while( path[i] != 0 ){
            if (path[i] == base){
                nextDest = path[i+1];
            }
        }
        return nextDest;
    }

    OpMode curMode;
}
