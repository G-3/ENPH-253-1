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
        HLRobot::Dir destDir = base->relDestDir(dest);
    }

    IntersectNav::~IntersectNav(){
       delete tapeFollower; 
    }

    //TODO remove knob controls from controller.

    // Note error is defined in the x direction with a robot to the right
    // of the tape having positive error.
    void IntersectNav::step(){
        bool xl = expectTapeDir[HLRobot::DirL];
        bool xr = expectTapeDir[HLRobot::DirR];
        bool xf = expectTapeDir[HLRobot::DirF];
        bool xlr = xl && xr;

        switch (curPhase):
            case INIT_ALIGN:
                // Align the intersection detectors 
                bool l = LLRobot::readRelQ
                bool r = LLRobot::readRelQ
                
                if(xlr){
                    // gotta rotate until it aligns
                    // need some state of what we've seen maybe
                } 
                else if((xl && l) || (xr && r)){
                    // we are good let's move on
                    curPhase = DriveThru;
                    return;
                }

            case DRIVE_THRU:
                // Drive until we activate our aligners
                // Read the alligners
                bool l = LLRobot::readRelQ
                bool r = LLRobot::readRelQ
               
                
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
                
                LLRobot::driveMotor(speed);
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
                if(destDir == HLRobot::DirL){
                    // turinging left
                    bool l = LLRobot::readRel
                    if(l){
                        // We tripped, move on
                        curPhase = TRIP_FOLLOW;
                    }

                }
                else if(destDir == HLRobot::DirR){
                    // turning right 
                    bool r = LLRobot::readRel
                    if(r){
                        // We tripped, move on
                        curPhase = TRIP_FOLLOW;
                    }

                }
                else{
                    //What?
                }

            case TRIP_FOLLOW:
                // Turn until we trip the tape followers
                if(destDir == HLRobot::DirL){
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
                else if(destDir == HLRobot::DirR){
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
