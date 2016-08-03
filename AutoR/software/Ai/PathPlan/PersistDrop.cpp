#include "PersistDrop.h"
#include "../World.h"
#include "../HLRobot.h"

using namespace World;
using namespace HLRobot;

namespace PathPlan{
    /*
     * Will persist until it reaches the drop off beacon.
     * Reroute until we get to node 13 or 3 and drive in between the two,
     * until we spot the beacon.
     */
    PersistDrop::PersistDrop(World::Node *destLast, World::Node *destBase) : ultimateLast(destLast), ultimateBase(destBase){
        baseCounter = 0;
        reroute();
        destNode = getNextDest(baseNode);
    }

    Node *PersistDrop::getNextDest(Node *base){
        Node *dest = 0;
        if(base == currentPath[baseCounter]){
            dest = currentPath[baseCounter + 1];
        }
        return dest;
    }
    
    void PersistDrop::update(){
        // if we entered the last stretch towards ultimateLast 
        // set destination to ultimateBase
        if (baseNode == ultimateLast){
            destNode = ultimateBase;   
        }
        // if we are heading towards ultimateBase 
        // bounce towards ultimateLast 
        else if(baseNode == ultimateBase){
            destNode = ultimateLast;
        }
        // otherwise just keep on following the path
        else{
            destNode = getNextDest(baseNode); 
        }
        if(destNode == 0){
            reroute();
            destNode = getNextDest(baseNode);
        }
    }

    void PersistDrop::finishedIntersect(){
        baseCounter += 1;
        
        lastNode = baseNode;
        baseNode = destNode;
        
        // if we entered the last stretch towards ultimateLast 
        // set destination to ultimateBase
        if (baseNode == ultimateLast){
            destNode = ultimateBase;   
        }
        // if we are heading towards ultimateBase 
        // bounce towards ultimateLast 
        else if(baseNode == ultimateBase){
            destNode = ultimateLast;
        }
        // otherwise just keep on following the path
        else{
            destNode = getNextDest(baseNode); 
        }
        if(destNode == 0){
            reroute();
            destNode = getNextDest(baseNode);
        } 
    }

    void PersistDrop::finishedTurnAround(){
        // if the node we were coming from was our destination, it was intended
        if(lastNode == currentPath[baseCounter + 1]){
            // shift to the next base
            baseCounter += 1;
            
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
            // TODO: decay these values
            // Update the edge weights so that we are discouraged from traversing
            lastNode->World::Node::setEdgeWeight(HLRobot::baseNode, 10);
            baseNode->World::Node::setEdgeWeight(HLRobot::lastNode, 10);

            // We want to find a new path to the dropOff 
            reroute();

            // set the counter to point to 0th element in the path which is now our base
            baseCounter = 0;
            
            // get the new destination
            destNode = getNextDest(baseNode);
        }
        if(destNode == 0){
            reroute();
            destNode = getNextDest(baseNode);
        }
    }
    
    void PersistDrop::reroute(){
        //Store paths for 3 and 13 then pick the shorter one
        uint16_t cost3 = World::updatePath(baseNode->id, ultimateLast->id, path3);
        uint16_t cost13 = World::updatePath(baseNode->id, ultimateBase->id, path13);
        baseCounter = 0;
        if(cost13 < cost3){
            // Node 13 provides the better path navigate towards it
            // Copy path 13 over
            for(uint8_t i = 0; i < MAX_PATH_LENGTH; i++){
                currentPath[i] = path13[i];
            }
        }
        else{
            // Node 3 provides the better path
            for(uint8_t i = 0; i < MAX_PATH_LENGTH; i++){
                currentPath[i] = path3[i];
            }           
        }
    }
}
