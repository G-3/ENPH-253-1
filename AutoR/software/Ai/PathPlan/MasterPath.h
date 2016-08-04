#pragma once 
#include "PathMode.h"

namespace World{
    class Node;
}

namespace PathPlan{
    /*
     * Will unconditionally follow the master path and fail if something unexpected happens.
     */
    class MasterPath : public PathMode{
        private:
            World::Node *masterPath[100] = {}; 
        public:
            MasterPath();
            ~MasterPath();
            World::Node *getNextDest(World::Node* base);
            void *finishedIntersect(World::Node *oldLast, 
                World::Node *last, 
                World::Node *base); 
            void *finishedTurnAround(World::Node *oldLast, 
                World::Node *last, 
                World::Node *base); 
    };
}
