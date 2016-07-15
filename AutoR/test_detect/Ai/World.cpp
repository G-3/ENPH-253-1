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
                case HLRobot::DirB: 
                    // The neighbor nodes array follows uses
                    // same convention for indexing
                    nodes[startID]->linked[HLRobot::DirB] = nodes[endID];
                    nodes[endID]->linked[HLRobot::DirF] = nodes[startID];

                case HLRobot::DirR: 
                    nodes[startID]->linked[HLRobot::DirR] = nodes[endID];
                    nodes[endID]->linked[HLRobot::DirL] = nodes[startID];

                case HLRobot::DirF: 
                    nodes[startID]->linked[HLRobot::DirF] = nodes[endID];
                    nodes[endID]->linked[HLRobot::DirB] = nodes[startID];

                case HLRobot::DirL: 
                    nodes[startID]->linked[HLRobot::DirL] = nodes[endID];
                    nodes[endID]->linked[HLRobot::DirR] = nodes[startID];           
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
                expectTapeDir[(startDir+i)%4] = 1;
            }
        }
    }

    HLRobot::Dir Node::relDestDir(Node *dest){
        for(int i=0; i<4; i++){
            if(linked[i]==dest){
                return i;
            }
        }
    }
}
