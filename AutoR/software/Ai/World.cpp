#include "World.h"

#include "HLRobot.h"
#include "Config.h"

#include "Debug.h"

#include <Arduino.h>

namespace World{
	Node *nodes[3] = {};

	// Rotates the specified direction 90*rotations degrees counterclockwise
	// and returns the resulting direction
	Dir rotate(Dir direction, int rotations) {
        // Add since Dir increases counterclockwise
		return (Dir) ((direction + rotations) % 4);
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
                nodes[startID] = new Node();
                char msg[20];
                sprintf(msg, "NodeS . %d . %d \n", i, startID);
                Debug::serialPrint(msg, Debug::INTERSECT_DB);
            }
            int endID = Config::links[i][1];
            if(!nodes[endID]){
                nodes[endID] = new Node();
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
                    nodes[endID]->linked[DirF] = nodes[startID];
                    break;

                case DirR: 
                    nodes[startID]->linked[DirR] = nodes[endID];
                    nodes[endID]->linked[DirL] = nodes[startID];
                    break;

                case DirF: 
                    nodes[startID]->linked[DirF] = nodes[endID];
                    nodes[endID]->linked[DirB] = nodes[startID];
                    break;

                case DirL: 
                    nodes[startID]->linked[DirL] = nodes[endID];
                    nodes[endID]->linked[DirR] = nodes[startID];           
                    break;
            }
        }
        HLRobot::lastNode = nodes[0];
        HLRobot::baseNode = nodes[1];
        HLRobot::destNode = nodes[2];
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
}
