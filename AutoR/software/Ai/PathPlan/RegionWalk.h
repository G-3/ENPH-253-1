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
            uint8_t curRegion;
            uint8_t nextRegion;
            uint8_t lastHub;
            uint8_t nextHub; 

            World::Node *currentPath[30] = {};
            uint8_t baseCounter = 0;

            static const uint8_t numRegions = 7;

            uint8_t biasCost[7] = {7, 5, 7, 5, 2, 7, 5};

            // Aditional costs of traversing the region dependent on the situation
            // F.e. don't want to traverse the same region back to back
            // Don't want to traverse region we have been bumped into right away
            uint8_t traversedCost[7] = {};
            uint8_t collisionCost[7] = {};

            uint8_t regionLengths[7] = {7, 7, 7, 7, 4, 7, 4};
            
            uint8_t Region0[7] = {4, 1, 0, 1, 2, 3, 4};
            uint8_t Region1[7] = {4, 5, 6, 5, 7, 5, 4};
            uint8_t Region2[7] = {14, 11, 10, 11, 12, 13, 14};
            uint8_t Region3[7] = {14, 15, 16, 15, 17, 15, 14};
            uint8_t Transition0[4] = {4, 3, 13, 14};
            uint8_t Transition1[7] = {4, 8, 19, 20, 19, 18, 14}; 
            uint8_t Transition2[4] = {14, 18, 8, 4}; 
            
            static const uint8_t defaultRegion = 6;
            
            static const uint8_t rightHub = 14;
            static const uint8_t leftHub = 4;

            /*
             * Returns list of nodes comprising this region.
             */
            uint8_t* getRegionPath(uint8_t region);

            /*
             * Get the cost of the region given our base.
             */
            uint8_t getRegionCost(uint8_t region, uint8_t base);
            
            /*
             * Returns the next region we should pursue based on current base.
             * If base is a hub will find the best region.
             * Otherwise finds any region we are on.
             */
            uint8_t getNextRegion(uint8_t base);
            
            /*
             * Updates our path to match the region we are in.
             * Assumes that the base is part of the region.
             */
            void updateRegionPath(uint8_t region, uint8_t base);

        public:
            RegionWalk();
            ~RegionWalk();
            World::Node *getNextDest(World::Node* base);
            
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
/*
    class Region{
        private:
            const uint8_t length;
        public:
            Region(uint8_t nodeBuf[], uint8_t length); 
    }
*/
}
