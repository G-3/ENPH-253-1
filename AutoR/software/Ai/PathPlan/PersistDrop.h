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
    class PersistDrop : public PathMode{
        private:
            uint8_t baseCounter = 0;
            static const uint8_t MAX_PATH_LENGTH = 30;
            // Two nodes describing ultimate destination of robot
            // PersistDrop will persist to either one and bounce in between
            // ultimateLast to ultimateBase
            // lastNode -> ultimateLast
            // baseNode -> ultimateBase
            // destNode -> NULL
            World::Node *ultimateLast = 0; 
            World::Node *ultimateBase = 0; 
            World::Node *currentPath[MAX_PATH_LENGTH] = {};
            World::Node *path3[MAX_PATH_LENGTH] = {};
            World::Node *path13[MAX_PATH_LENGTH] = {};
            
            /*
             * Maps a new path towards ultimateLast or ultimateBase
             */ 
            void reroute();
        public:
            PersistDrop(World::Node *destLast, World::Node *destBase);
            ~PersistDrop();
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
  
            void finishedPickUp(){};
            
            void finishedDropOff(){};

    };
}
