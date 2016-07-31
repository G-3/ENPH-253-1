#include "PersistDest.h"
#include "../World.h"
#include "../HLRobot.h"

using namespace World;
using namespace HLRobot;

namespace PathPlan{
    PersistDest::PersistDest(World::Node *destLast, World::Node *destBase) : ultimateLast(destLast), ultimateBase(destBase){
        baseCounter = 0;
        World::updatePath(baseNode->id, ultimateLast->id, currentPath);
        destNode = getNextDest(baseNode);
    }

    Node *PersistDest::getNextDest(Node *base){
        Node *dest = 0;
        if(base == currentPath[baseCounter]){
            dest = currentPath[baseCounter + 1];
        }
        return dest;
    }
    
    void PersistDest::update(){
        destNode = getNextDest(baseNode);
    }

    void PersistDest::finishedIntersect(){
        baseCounter += 1;
        
        lastNode = baseNode;
        baseNode = destNode;
        
        // if we entered the last stretch towards ultimateLast 
        // set destination to ultimateBase
        if (baseNode == ultimateLast){
            destNode = ultimateBase;   
        }
        // if we are heading towards ultimateBase from ultimateLast, 
        // there is no more destination
        else if(baseNode == ultimateBase && lastNode == ultimateLast){
            destNode = 0;
        }
        // otherwise just keep on following the path
        else{
            destNode = getNextDest(baseNode); 
        }
    }

    void PersistDest::finishedTurnAround(){
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
            destNode = getNextDest(baseNode);
            // TODO: decay these values
            // Update the edge weights so that we are discouraged from traversing
            lastNode->World::Node::setEdgeWeight(HLRobot::baseNode, 10);
            baseNode->World::Node::setEdgeWeight(HLRobot::lastNode, 10);

            // We want to find a new path to the first destination node
            World::updatePath(baseNode->id, ultimateLast->id, currentPath);
            
            // set the counter to point to 0th element in the path which is now our base
            baseCounter = 0;
            
            // get the new destination
            destNode = getNextDest(baseNode); 
        }
    }
}
