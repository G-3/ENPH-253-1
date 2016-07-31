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
    class RegionWalk : public PathMode{
        private:
            uint8_t baseCounter = 0;
            uint8_t regionWeights[7] = {};
            uint8_t regionLengths[7] = []
            uint8_t Region0[] = {4, 1, 0, 1, 2, 3, 4};
            uint8_t Region1[] = {4, 5, 6, 5, 7, 5, 4};
            uint8_t Region2[] = {4, 8, 19, 20, 19, 18, 14}; 
            uint8_t Region3[] = {14, 18, 8, 4}; 
            uint8_t Region4[] = {14, 15, 16, 15, 17, 15, 14};
            uint8_t Region5[] = {14, 11, 10, 11, 12, 13, 14};
            uint8_t Region6[] = {4, 3, 13, 14}; 
            
            World::Node *currentPath[100] = {};
        public:
            RegionWalk(World::Node *destLast, World::Node *destBase);
            ~RegionWalk();
            World::Node *getNextDest(World::Node* base);

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
/*
    class Region{
        private:
            const uint8_t length;
        public:
            Region(uint8_t nodeBuf[], uint8_t length); 
    }
*/
}
