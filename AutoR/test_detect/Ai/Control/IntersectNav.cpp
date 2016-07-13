#include "IntersectNav.h"
#include "TapeFollow.h"

namespace Control{
    /*
     * Tape Following Mode
     */
    IntersectNav::IntersectNav(){
        tapeFollower = new TapeFollow();
    }

    IntersectNav::~IntersectNav(){
       delete tapeFollower; 
    }

    //TODO remove knob controls from controller.

    // Note error is defined in the x direction with a robot to the right
    // of the tape having positive error.
    void IntersectNav::step(){
    }
}
