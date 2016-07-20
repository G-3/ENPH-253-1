#pragma once
#include <Arduino.h>

namespace World{
	enum Dir { DirINVALID = -1, DirB = 0, DirR = 1, DirF = 2, DirL = 3 };

	Dir rotate(Dir direction, int rotations);

	class Node {
	public:
		bool deadEnd;
        int8_t id = -1;
		Node(int id) : id(id), deadEnd(false) {
            weights[0] = 1;
            weights[1] = 1;
            weights[2] = 1;
            weights[3] = 1;
        };
		Node *linked[4] = {};
        uint16_t weights[4];
		void relLinkDirs(bool expectTapeDir[4], Node *start);
		Dir relDestDir(Node *dest, Node *start);
	};

    void updatePath(uint8_t src, uint8_t target);

    int minDistance(uint16_t dist[], bool Q[], uint8_t length);

    void setup();
    
    // links describes all edges on the board 
    extern Node *nodes[19];
    const uint8_t nodesSize = 19;
}