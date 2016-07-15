#pragma once

namespace World{
    void setup();
    
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
            HLRobot::Dir relDestDir(Node *dest, Node *base);`
    }
}
