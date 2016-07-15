#include "World.h"

namespace World{
    Board::Board(){
        for (int i=0; i<::Config::linksSize; i++;){
            int startID = links[i][0];
            if(!nodes[startID]){
                nodes[startID] = new Node();
            }
            int endID = links[i][1];
            if(!nodes[endID]){
                nodes[endID] = new Node();
            }
            
            // here dir is the direction of the end note
            // relative to the start node
            int dir = links[i][2];
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

    void Node::relLinkDirs(bool[] expectTapeDir, Node *start){
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
                expectTapeDir[rotate(i, startDir)] = 1;
            }
            else{
                expectTapeDir[rotate(i, startDir)] = 0; 
            }
        }
    }

    Dir Node::relDestDir(Node *dest, Node *start){
        Dir startDir = DirINVALID;
        for(int i=0; i<4; i++){
            if(linked[i]==start){
                startDir = i;
                break;
            }
        }
        if (startDir == DirINVALID){
            return DirINVALID;
        }
        for(int i=0; i<4; i++){
            if(linked[i]==dest){
                return rotate(i, startDir);
            }
        }
        return DirINVALID;
    }

    Dir rotate(Dir direction, int rotations){
        return (direction + rotations)%4;
    }
}
