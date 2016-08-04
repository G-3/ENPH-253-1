#pragma once 
#include <Arduino.h>
#include "PathMode.h"

namespace World{
    class Node;
}

namespace PathPlan{
    /*
     * Will continuously and persistently navigate towards a particular node.
     * Replanning when collided.
     */
    class PersistDest : public PathMode{
        private:
            uint8_t baseCounter = 0;
            
            // Two nodes describing ultimate destination of robot
            // PersistDest will be complete when robot is going from
            // ultimateLast to ultimateBase
            // lastNode -> ultimateLast
            // baseNode -> ultimateBase
            // destNode -> NULL
            World::Node *ultimateLast = 0; 
            World::Node *ultimateBase = 0; 
            World::Node *currentPath[100] = {};
        public:
            PersistDest(World::Node *destLast, World::Node *destBase);
            ~PersistDest();
            World::Node *getNextDest(World::Node *base);

            /*
             * Ensures that the planner is up to date
             */
            void update();

            /*
             * Handels completion of intersection.
             * @modify lastNode : The entry point of the intersection
             * @modify baseNode : The intersection itself
             * @modify destNode : The exit point of the intersection
             */
            void finishedIntersect(); 
            
            /*
             * Handels completion of turn around.
             * @modify lastNode : The entry node of the edge where we turned around
             * @modify baseNode : The exit node of the edge where we turned around
             */
            void finishedTurnAround(); 
    };
}
