#pragma once

namespace Event{
    class EDetect{
	private:
	    EDetect(){};
	    int count = 0;
	public:
	    void step();
    };

    void checkIntersect();
};
