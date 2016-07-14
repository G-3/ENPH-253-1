#include "World.h"

namespace World{
    class Board{
        Board(){
            for (int i=0; i<::Config::linksSize; i++;){
                int startID = links[i][0];
                if(!nodes[startID]){
                    nodes[startID] = new Node();
                }
                int endID = links[i][1];
                if(!nodes[endID]){
                    nodes[endID] = new Node();
                }
                
                int dir = links[i][2];
                switch{
                    case 0: 
                        nodes[startID][0] = nodes[endID];
                        nodes[endID][2] = nodes[startID];

                    case 1: 
                        nodes[startID][1] = nodes[endID];
                        nodes[endID][3] = nodes[startID];
 
                    case 2: 
                        nodes[startID][2] = nodes[endID];
                        nodes[endID][0] = nodes[startID];

                    case 3: 
                        nodes[startID][3] = nodes[endID];
                        nodes[endID][1] = nodes[startID];           
                }
            }
        }
    }
}
