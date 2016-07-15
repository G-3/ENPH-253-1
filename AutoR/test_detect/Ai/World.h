#pragma once

namespace World{
    void setup();
    enum Dir{DirINVALID=-1, DirB=0,DirR=1,DirF=2,DirL=3};
    
    // links describes all edges on the 
    Node *nodes[3] = {};
    const int nodesSize = 3;
    
    class Board{
        public:
            Board();
    }
    
    class Node{
        public:
            bool deadEnd;
            Node() : deadEnd(false) {};
            Node *linked[4]={};
            void relLinkDirs(bool[] expectTapeDir, Node *start, Node *end);
            Dir relDestDir(Node *dest, Node *base);
    }
}
