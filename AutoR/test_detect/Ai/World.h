#pragma once

namespace World{
	enum Dir { DirINVALID = -1, DirB = 0, DirR = 1, DirF = 2, DirL = 3 };

	Dir rotate(Dir direction, int rotations);

	class Node {
	public:
		bool deadEnd;
		Node() : deadEnd(false) {};
		Node *linked[4] = {};
		void relLinkDirs(bool expectTapeDir[4], Node *start);
		Dir relDestDir(Node *dest, Node *start);
	};

    void setup();
    
    // links describes all edges on the board 
    extern Node *nodes[3];
    const int nodesSize = 3;
}
