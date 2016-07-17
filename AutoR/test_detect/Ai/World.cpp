#include "World.h"
#include "Config.h"

namespace World{
	Node *nodes[3] = {};

	// Rotates the specified direction 90 degrees counterclockwise
	// and returns the resulting direction
	Dir rotate(Dir direction, int rotations) {
		return (Dir) ((direction + rotations) % 4);
	}

    Board::Board(){
        for (int i=0; i<Config::linksSize; i++){
            int startID = Config::links[i][0];
            if(!nodes[startID]){
                nodes[startID] = new Node();
            }
            int endID = Config::links[i][1];
            if(!nodes[endID]){
                nodes[endID] = new Node();
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

                case DirR: 
                    nodes[startID]->linked[DirR] = nodes[endID];
                    nodes[endID]->linked[DirL] = nodes[startID];

                case DirF: 
                    nodes[startID]->linked[DirF] = nodes[endID];
                    nodes[endID]->linked[DirB] = nodes[startID];

                case DirL: 
                    nodes[startID]->linked[DirL] = nodes[endID];
                    nodes[endID]->linked[DirR] = nodes[startID];           
            }
        }
    }

    void Node::relLinkDirs(bool expectTapeDir[4], Node *start){
        int startDir;
        for(int i=0; i<4; i++){
            if(linked[i]==start){
                startDir = i;
                break;
            }
        }
        for(int i=0; i<4; i++){
            if(linked[i]){
                //This shifts the directions by startDir
                expectTapeDir[rotate((Dir)i, startDir)] = 1;
            }
            else{
                expectTapeDir[rotate((Dir)i, startDir)] = 0; 
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
                return rotate( (Dir) i, startDir);
            }
        }
        return DirINVALID;
    }
}
