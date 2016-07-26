#include "World.h"

#include "HLRobot.h"
#include "Config.h"

#include "Debug.h"

#include <Arduino.h>


#define DIST_MAX (1000)

namespace World{
	Node *nodes[NUM_NODES] = {};

	// Rotates the specified direction 90*rotations degrees counterclockwise
	// and returns the resulting direction
	Dir rotate(Dir direction, int rotations) {
        // Add since Dir increases counterclockwise
        // Get rid of negative remainder case by adding 4 and modulus again
		return (Dir) ((((direction + rotations) % 4) + 4) % 4);
	}
    
    //TODO: Change node system to have double edges since some edges
    //      bend in direction aka leaves start node on left but curves
    //      in to dest node at top.
    void setup(){
        // Loop over all the pre-configured edges
        for (int i=0; i<Config::linksSize; i++){
            Debug::serialPrint("Link", Debug::INTERSECT_DB);
            // Initialize nodes of the given edge
            int startID = Config::links[i][0];
            if(!nodes[startID]){
                nodes[startID] = new Node(startID);
                char msg[20];
                sprintf(msg, "NodeS . %d . %d \n", i, startID);
                Debug::serialPrint(msg, Debug::INTERSECT_DB);
            }
            int endID = Config::links[i][1];
            if(!nodes[endID]){
                nodes[endID] = new Node(endID);
                char msg[20];
                sprintf(msg, "NodeE . %d . %d \n", i, endID);
                Debug::serialPrint(msg, Debug::INTERSECT_DB);
            }
            
            // here dir is the direction of the end note
            // relative to the start node
            int dir = Config::links[i][2];
            switch(dir){
                case DirB: 
                    // The neighbor nodes array follows uses
                    // same convention for indexing
                    nodes[startID]->linked[DirB] = nodes[endID];
                    break;

                case DirR: 
                    nodes[startID]->linked[DirR] = nodes[endID];
                    break;

                case DirF: 
                    nodes[startID]->linked[DirF] = nodes[endID];
                    break;

                case DirL: 
                    nodes[startID]->linked[DirL] = nodes[endID];
                    break;
            }
        }
    }

    void Node::relLinkDirs(bool expectTapeDir[4], Node *start){
        Dir startDir;
        for(int i=0; i<4; i++){
            if(linked[i]==start){
                startDir = (Dir)i;
                Debug::serialPrint("Start direction found.", Debug::INTERSECT_DB);
                break;
            }
        }
        for(int i=0; i<4; i++){
            if(linked[i]){
                char msg[30];
                sprintf(msg, "Start: %d\nActual %d \n", startDir, i);
                Debug::serialPrint(msg, Debug::INTERSECT_DB);

                // Want to see what the direction of the tape is in the new reference frame
                // This is the exact inverse of rotating it by the offset of the new reference frame
                expectTapeDir[rotate((Dir)i, 4-startDir)] = 1;
            }
            else{
                char msg[30];
                sprintf(msg, "NULL %d \n", i);
                Debug::serialPrint(msg, Debug::INTERSECT_DB);
                expectTapeDir[rotate((Dir)i, 4-startDir)] = 0; 
            }
        }
    }

    Dir Node::relDestDir(Node *dest, Node *start){
        Dir startDir = DirINVALID;
        for(int i=0; i<4; i++){
            if(linked[i]==start){
                startDir = (Dir) i;
                break;
            }
        }
        if (startDir == DirINVALID){
            return DirINVALID;
        }
        for(int i=0; i<4; i++){
            if(linked[i]==dest){
                return rotate( (Dir) i, 4-startDir);
            }
        }
        return DirINVALID;
    }

    void updatePath(uint8_t src, uint8_t target){
        uint8_t n = NUM_NODES;
        uint8_t prev[n];    // previous node in optimal path from source
        uint16_t dist[n];    // distance from source to i
        bool Q[n];      // set of visited nodes Q, true if visited

        // Initialize all distances as INFINITE and unvisited
        for (int i = 0; i < n; i++){
            dist[i] = DIST_MAX, Q[i] = false;
        }

        dist[src] = 0;

        // Find shortest path for all vertices
        for (uint8_t count = 0; count < n-1; count++)
        {
            // visit closest unvisited node 
            uint8_t u = minDistance(dist, Q, n);

            Q[u] = true;
            
            // if it is the target, we are done
            if(u == target) break;

            // Loop over possible connections for node u
            for (uint8_t v = 0; v < 4; v++){
                //Get weight in the v direction
                uint16_t weight = nodes[u]->weights[v];
                Node *nodev = nodes[u]->linked[v];
                if(nodev){                                  // node exists in this direction
                    if (!Q[nodev->id]                       // not visited
                        && dist[u] + weight < dist[nodev->id]       // is it shorter than what we have now
                    ){
                        dist[nodev->id] = dist[u] + weight;         // then update the shortest distance
                        prev[nodev->id] = nodes[u]->id;             // store how we got their for backtrack
                   }  
               }
            }
        }
        Node *tempPath[n];          // Stack the nodes of the path starting from the target
        int trackBack = target;
        int pathLength = 0;
        while (trackBack != src){   // We don't push the source
            tempPath[pathLength] = nodes[trackBack];
            trackBack = prev[trackBack];
            pathLength += 1;
        }
        
        // tempPath is reversed since we started from the end, we should invert when assigning path
        for (int i = pathLength; i >= 0; i--) {
            HLRobot::path[pathLength-i] = tempPath[i];
        }
        HLRobot::path[pathLength] = 0;
    }

    int minDistance(uint16_t dist[], bool Q[], uint8_t length){
        int minDist = DIST_MAX+1;
        int u = 0;
        for (int i = 0; i < length; i++){
            // if its not visited and its distance is smaller, update
            if (!Q[i] && dist[i] < minDist){
                minDist = dist[i];
                u = i;
            }
        }
        return u;
    }
}
