#include "HLRobot.h"
#include "World.h"

namespace HLRobot {
    World::Node *lastNode;
    World::Node *baseNode;
    World::Node *destNode;
    World::Node *path[Config::linksSize] = {};
	
    OpMode curMode;
}
