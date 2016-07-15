#include "IntersectNav.h"
#include "TapeFollow.h"

namespace Control{
    /*
     * Tape Following Mode
     */
    IntersectNav::IntersectNav(Node *start, Node *dest, Node *base): start(start), dest(dest), base(base){
        tapeFollower = new TapeFollow();
        speed = 100;
        curPhase = DThru;
        base->relLinkDirs(expectTapeDir, start, end);
        World::Dir destDir = base->relDestDir(dest);
    }

    IntersectNav::~IntersectNav(){
       delete tapeFollower; 
    }

    //TODO remove knob controls from controller.

    // Note error is defined in the x direction with a robot to the right
    // of the tape having positive error.
    void IntersectNav::step(){
        bool xl = expectTapeDir[World::DirL];
        bool xr = expectTapeDir[World::DirR];
        bool xf = expectTapeDir[World::DirF];
        bool xlr = xl && xr;

        switch (curPhase):
            case INIT_ALIGN:
                // Align the intersection detectors after detection 
                bool l = LLRobot::readRelQ
                bool r = LLRobot::readRelQ
                

                if(!(xl||xr)){
                    if(l||r){
                        // This wasn't supposed to happen
                        // we weren't expecting a cross edge
                        
                    }
                }
                if(xlr){
                    // gotta rotate until it aligns
                    // need some state of what we've seen maybe
                } 
                else if(l && r){
                    // Only one was supposed to be tripped
                }
                else if((xl && l) || (xr && r)){
                    // we are good let's move on
                    curPhase = DriveThru;
                    return;
                }
                else if(l||r){
                    // We messed up, trip on an unexpected side
                }
                else{
                    //Precondition not matched, we aren't actually on tape
                }

            case DRIVE_THRU:
                // Drive until we activate our aligners
                // Read the alligners
                bool l = LLRobot::readRelQ
                bool r = LLRobot::Rel::readRelQ
               
                
                if(xlr){
                    if(l || r){
                        curPhase = INTER_ALIGN;
                        return;
                    }
                }
                
                else if(xr){
                    // only right should be tripped
                    if(r){
                        curPhase = TRIP_INTER;
                        return;
                    }
                    else if(l){
                        // we done fuck it up
                        falseIntersect();
                    }
                    
                }

                else if(xl){
                    // only left should be tripped
                    if(l){
                        curPhase = TRIP_INTER;
                        return;
                    }
                    else if(r){
                        // we done fuck it up
                        falseIntersect();
                    }
                }    
                
                LLRobot::Rel::driveMotor(LLRobotspeed);
                LLRobot::driveMotor(speed);

            case INTER_ALIGN:
                // Align the intersection aligners
                if(!xlr){
                    // What are we doing?
                }
                else{
                    //Some state stuff
                }


            case TRIP_INTER:
                // Turn until we trip the intersection detector
                if(destDir == World::DirL){
                    // turinging left
                    bool l = LLRobot::readRel
                    if(l){
                        // We tripped, move on
                        curPhase = TRIP_FOLLOW;
                    }

                }
                else if(destDir == World::DirR){
                    // turning right 
                    bool r = LLRobot::readRel
                    if(r){
                        // We tripped, move on
                        curPhase = TRIP_FOLLOW;
                    }
 
                    LLRobot::driveMotor(speed);
                    LLRobot::driveMotor(speed);


                }
                else{
                    //What?
                }

            case TRIP_FOLLOW:
                // Turn until we trip the tape followers
                if(destDir == World::DirL){
                    // Check if we trip the TF
                    bool l = LLRobot::read
                    if(l){
                        //Gottem we are done
                        currPhase = END;
                        return;
                    }
                    else{ 
                        LLRobot::driveMotor(speed);
                        LLRobot::driveMotor(speed);
                    }

                }
                else if(destDir == World::DirR){
                    // Check if we trip the TF
                    bool l = LLRobot::read
                    if(l){
                        //Gottem we are done
                        currPhase = END;
                        return;
                    }
                    else{ 
                        LLRobot::driveMotor(speed);
                        LLRobot::driveMotor(speed);
                    }
                }
            
            case END:
                // Call da event handler       
                 
    }
}
