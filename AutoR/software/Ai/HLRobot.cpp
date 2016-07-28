#include "HLRobot.h"
#include "World.h"

namespace HLRobot {
    World::Node *lastNode;
    World::Node *baseNode;
    World::Node *destNode;
    World::Node *path[Config::linksSize] = {};
    uint8_t pathCounter = 0;

    World::Node *getNextDest(World::Node* base){
        World::Node *nextDest = 0;
        /*
        uint8_t i = 0;
        while( path[i] != 0 ){
            if (path[i] == base){
                nextDest = path[i+1];
                break;
            }
            i+=1;
        }*/
        if ( path[pathCounter] == base ){
            pathCounter += 1;
            nextDest = path[pathCounter];
        }
        return nextDest;
    }

    OpMode curMode;
}
