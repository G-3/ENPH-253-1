#pragma once

namespace World{
    class Node;
}

namespace PathPlan{
    class PathMode{
        public:            
            virtual World::Node *getNextDest(World::Node *base) = 0;
            
            /*
             * Assures that the path planner is up to date  
             */
            virtual void update() = 0; 

            /*
             * Handels completion of intersection.
             * @modify lastNode : The entry point of the intersection
             * @modify baseNode : The intersection itself
             * @modify destNode : The exit point of the intersection
             */
            virtual void finishedIntersect() = 0;
            
            /*
             * Handels completion of turn around.
             * @modify lastNode : The entry node of the edge where we turned around
             * @modify baseNode : The exit node of the edge where we turned around
             */
            virtual void finishedTurnAround() = 0;
            
            virtual void finishedPickUp() = 0;
            
            virtual void finishedDropOff() = 0;
    };
}
