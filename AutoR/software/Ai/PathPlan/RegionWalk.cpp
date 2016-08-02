#include "RegionWalk.h"
#include <Arduino.h>
#include <phys253.h>
#include "../World.h"
#include "../HLRobot.h"

using namespace World;
using namespace HLRobot;

namespace PathPlan{
    RegionWalk::RegionWalk(){
        dropOffPlanner = new PersistDrop(nodes[3], nodes[13]);
        if(hasPassenger()){
            curMode = PERSIST;
        }
        else{
            curMode = WALK;
        }
        baseCounter = 0;
        curRegion = getNextRegion(baseNode->id);
        updateRegionPath(curRegion, baseNode->id);
   }
    RegionWalk::~RegionWalk(){
        delete dropOffPlanner;
    } 

   Node *RegionWalk::getNextDest(Node *base){
        Node *dest = 0;
        if(base == currentPath[baseCounter]){
            dest = currentPath[baseCounter + 1];
        }
        else {
            LCD.clear(); 
            LCD.home(); 
            LCD.print("WrongBase"); 
        }
        LCD.setCursor(0, 1);
        LCD.print(dest->id); 
        return dest;
    }
    
    uint8_t RegionWalk::getNextRegion(uint8_t base){
        // If it's a hub find the best region
        if(base == rightHub || base == leftHub){
            // Find the region that has the lowest cost to us
            uint8_t bestRegion = defaultRegion;
            uint8_t minCost = getRegionCost(defaultRegion, base); 
            for(int i = 0; i < numRegions; i++){

                uint8_t *rPath = getRegionPath(i);
                uint8_t rl = regionLengths[i]; 
               
                // Check that the region starts from this hub
                if( base == rPath[0] || base == rPath[rl-1] ){
                    uint8_t regionCost = getRegionCost(i, base);
                    if (regionCost < minCost){
                        bestRegion = i;
                        minCost = regionCost;
                    }
                }
            }
            return bestRegion;
        }
        // Otherwise just find the first usable one
        else{
            // Pick the first region that contains our base
            for (int i = 0; i < numRegions; i++){
                 uint8_t *path = getRegionPath(i);
                 uint8_t n = regionLengths[i];
                 for (int j = 0; j < n; j++){
                    if(path[j] == base){
                        return i;
                    } 
                 }
            }
        }
        // Should never get here
    }

    uint8_t* RegionWalk::getRegionPath(uint8_t region){
        switch(region){
            case 0:
                return Region0;
            case 1:
                return Region1;
            case 2:
                return Region2;
            case 3:
                return Region3;
            case 4:
                return Transition0;
            case 5:
                return Transition1;
            case 6:
                return Transition2;
        }
    }

    uint8_t RegionWalk::getRegionCost(uint8_t region, uint8_t base){
        uint8_t totalCost = 0;
        totalCost += biasCost[region];
        totalCost += traversedCost[region];
        totalCost += collisionCost[region];

        // For transitions take into account the cost of the regions on the
        // other side compared to the ones on this side 
        
        return totalCost;
    }

    void RegionWalk::updateRegionPath(uint8_t region, uint8_t base){
        uint8_t *rPath = getRegionPath(region);
        uint8_t rl = regionLengths[region];
        
        uint8_t regionPos;
        //Find our base along the region and set our baseCounter accordingly
        for(int i = 0; i < rl; i++){
            if(base == rPath[i]){
                regionPos = i;
                break;
            } 
        }
        
        // Check if we are at the end, if so travel in reverse
        if(regionPos == rl-1){
            // Write region path to current but in reverse
            for(int i = 0; i < rl; i++){
                currentPath[i] = nodes[rPath[rl-1-i]];
            }
            currentPath[rl] = 0; 
        
            // Set the last visited hub to the end of our region(reversed).
            lastHub = rPath[rl-1];
            // And nextHub to the start of our region(reversed).
            nextHub = rPath[0];

            // Set the baseCounter but you got to flip it
            baseCounter = (rl-1) - regionPos;
        }
        else{
            // Write the region path to our current path.
            for(int i = 0; i < rl; i++){
                currentPath[i] = nodes[rPath[i]];
            }
            // NULL ptr to signal end of path
            currentPath[rl] = 0; 
            
            // Set the last visited hub to the start of our region.
            lastHub = rPath[0];
            // And nextHub to the end of our region.
            nextHub = rPath[rl-1];

            // Set the baseCounter
            baseCounter = regionPos;
        }
    }
    
    void RegionWalk::decayCosts(){
        for(int i = 0; i < numRegions; i++){
            int resultT = (int) traversedCost[i] - 2;
            if (resultT < 0){
                traversedCost[i] = 0;
            }
            else{
                traversedCost[i] = resultT;
            }
            
            int resultC = (int) collisionCost[i] - 2;
            if (resultC < 0){
                collisionCost[i] = 0;
            }
            else{
                collisionCost[i] = resultC;
            }
        }
    }
    
    void RegionWalk::update(){
         switch(curMode){
            case PERSIST:
            {
                dropOffPlanner->update();
                break;
            }
            
            case WALK:
            {
                // if we are heading towards the final destination of the region
                // we should update to the next region
                if(baseNode->id == nextHub && getNextDest(baseNode) == 0){
                    traversedCost[curRegion] = 10;
                    curRegion = getNextRegion(baseNode->id);
                    updateRegionPath(curRegion, baseNode->id);
                    
                    destNode = getNextDest(baseNode);
                   /* 
                    LCD.clear(); 
                    LCD.home(); 
                    LCD.print("nextR");LCD.setCursor(0, 1); 
                    LCD.print(destNode->id);LCD.print(" ");LCD.print(curRegion);
                    LCD.print(" ");LCD.print(currentPath[0]->id);
                    LCD.print(" ");LCD.print(currentPath[1]->id);
                    */
                }
                // otherwise just keep on following the path
                else{
                    destNode = getNextDest(baseNode); 
                   /* 
                    LCD.clear(); 
                    LCD.home(); 
                    LCD.print("goOn");LCD.setCursor(0, 1); 
                    LCD.print(destNode->id);LCD.print(" ");LCD.print(baseNode->id);
                    LCD.print(" ");LCD.print(nextHub);
                    */
                } 
                break;
            }
        }
    }

    void RegionWalk::finishedIntersect(){
        switch(curMode){
            case PERSIST:
            {
                dropOffPlanner->finishedIntersect();
                break;
            }
            
            case WALK:
            {
                lastNode = baseNode;
                baseNode = destNode;
                
                // if we are heading towards the final destination of the region
                // and this is the last destination on our path
                // we should update to the next region
                if( baseNode->id == nextHub && getNextDest(baseNode) == 0 ){
                    traversedCost[curRegion] = 10;
                    curRegion = getNextRegion(baseNode->id);
                    updateRegionPath(curRegion, baseNode->id);

                    destNode = getNextDest(baseNode);
                    LCD.clear(); 
                    LCD.home(); 
                    LCD.print("fnextR");LCD.setCursor(0, 1); 
                    LCD.print(destNode->id);LCD.print(" ");LCD.print(curRegion);
                    LCD.print(" ");LCD.print(currentPath[0]->id);
                    LCD.print(" ");LCD.print(currentPath[1]->id);
                    LCD.print(" ");LCD.print(baseCounter);
                }
                // otherwise just keep on following the path
                else{
                    baseCounter += 1;
                    destNode = getNextDest(baseNode);
                    decayCosts();
                }
                break;
            }
        }
    }

    void RegionWalk::finishedTurnAround(){
        // Switch between our walk and the dropOffPlanner
        switch(curMode){
            case PERSIST:
            {
                dropOffPlanner->finishedTurnAround();
                break;
            }
            
            case WALK:
            {
                // if the node we were coming from was our destination, it was intended
                if(lastNode == currentPath[baseCounter + 1]){
                    // shift to the next base
                    baseCounter += 1;
                    decayCosts();
                    
                    // we are going to where we were coming from
                    Node *oldLastNode = lastNode;
                    lastNode = baseNode;
                    baseNode = oldLastNode;
                    destNode = getNextDest(baseNode);
                }
                // if it was unintentional we want to remap
                else{
                    Node *oldLastNode = lastNode;
                    lastNode = baseNode;
                    baseNode = oldLastNode;
                    
                    collisionCost[curRegion] = 10;
                    // TODO: decay these values
                    // Update the edge weights so that we are discouraged from traversing
                    lastNode->World::Node::setEdgeWeight(HLRobot::baseNode, 10);
                    baseNode->World::Node::setEdgeWeight(HLRobot::lastNode, 10);

                    // We want to find a new path to the lastHub we were at 
                    World::updatePath(baseNode->id, lastHub, currentPath);
                    nextHub = lastHub; 
                    // set the counter to point to 0th element in the path which is now our base
                    baseCounter = 0;
                    
                    // get the new destination
                    destNode = getNextDest(baseNode); 
                }
                break;
            }
        }
    }

    void RegionWalk::finishedPickUp(){
        if(hasPassenger()){
            curMode = PERSIST;
        }
        else{
            curMode = WALK;
        } 
    }

    void RegionWalk::finishedDropOff(){
        if(hasPassenger()){
            curMode = PERSIST;
        }
        else{
            curMode = WALK;
        }   
    }
}
