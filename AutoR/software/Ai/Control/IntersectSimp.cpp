#include "IntersectSimp.h"

#include "TapeFollow2.h"
#include "../World.h"
#include "../LLRobot.h"
#include "../EHandler.h"

#include <phys253.h>

#include <Arduino.h>
#include "../Debug.h"

using namespace LLRobot::Rel;
using namespace EHandler;

namespace Control{
    /*
     * Tape Following Mode
     */
    IntersectSimp::IntersectSimp(World::Node *start, World::Node *base, World::Node *dest): start(start), dest(dest), base(base){
        tapeFollower = new TapeFollow2(17,25,80);
        speed = 70;
        curPhase = DRIVE_THRU;
        base->relLinkDirs(expectTapeDir, start);
        destDir = base->relDestDir(dest, start);
       /* 
        Debug::serialPrint("Direction . Exp Tape \n", Debug::INTERSECT_DB);
        for(int i = 0; i < 4; i++){
            char msg[20];
            sprintf(msg, "%d . %d \n", i, expectTapeDir[i]);
            Debug::serialPrint(msg, Debug::INTERSECT_DB);
        }
        char msg[20];
        sprintf(msg, "Dest Dir %d \n", destDir);
        Debug::serialPrint(msg, Debug::INTERSECT_DB);
        */
    }

    IntersectSimp::~IntersectSimp(){
       delete tapeFollower; 
    }

    // Note error is defined in the x direction with a robot to the right
    // of the tape having positive error.
    void IntersectSimp::step(){
        bool xl = expectTapeDir[World::DirL];
        bool xr = expectTapeDir[World::DirR];
        bool xf = expectTapeDir[World::DirF];
        bool xlr = xl && xr;
        

        // we are looking to travel forward, follow tape while tracking the intersection
        // there should be at least one other direction
        // need to keep track of when we are done the intersection
        if (destDir == World::DirF){
            switch(curPhase){
                case DRIVE_THRU:
                {
                    // Check our aligners
                    bool l = readQRD(INL, true);
                    bool r = readQRD(INR, true);

                    if (l || r){
                        // We are done
                        curPhase = END;
                    }
                    tapeFollower->step();
                    break;
                }

                case END:
                    // DONE:
                    finishIntersect();
                    break;
            }
        }

        // Turning right or left with no tape to follow
        //else 
        else if(!xf){
            switch(curPhase){
                case DRIVE_THRU:
                {
                    driveMotors(speed, speed);
                    bool l = readQRD(INL, true);
                    bool r = readQRD(INR, true);

                    if (l || r){
                        driveMotors(0, 0);
                        curPhase = TRIP_INTER;
                        return;
                    }
                    break;
                }
                
                case TRIP_INTER:
                {
                    // Turn until we trip the intersection detectors
                    if (destDir == World::DirL) {
                        driveMotors(-speed, speed);
                        // turning left
                        bool l = readQRD(IDLF, true);
                        if (l) {
                            // We tripped, move on
                            driveMotors(0, 0);
                            curPhase = TRIP_FOLLOW;
                        }
                    }
                    else{
                        driveMotors(speed, -speed);
                        // turning right
                        bool r = readQRD(IDRF, true);
                        if (r) {
                            // We tripped, move on
                            driveMotors(0, 0);
                            curPhase = TRIP_FOLLOW;
                        }
                    }
                    break;
                }

                case TRIP_FOLLOW:
                {
                    // Turn until we trip the tape followers
                    if (destDir == World::DirL) {
                        // Check if we trip the TF
                        bool l = readQRD(TFLF, true);
                        if (l) {
                            //Gottem we are done
                            driveMotors(0, 0);
                            curPhase = END;
                            return;
                        }
                        else {
                            driveMotors(-speed, speed);
                        }
                    }
                    else{
                        // Check if we trip the TF
                        bool r = readQRD(TFRF, true);
                        if (r) {
                            driveMotors(0, 0);
                            //Gottem we are done
                            curPhase = END;
                            return;
                        }
                        else {
                            driveMotors(speed, -speed);
                        }
                    }
                    break;
                }

                case END:
                {
                    driveMotors(0, 0);
                    //DONE:
                    finishIntersect();
                    break;
                }
            }
        }

        // Turn at the intersection and there is a follow through path
        else{
            switch (curPhase) {
                
                case DRIVE_THRU:
                {
                    // Check our aligners
                    bool l = readQRD(INL, true);
                    bool r = readQRD(INR, true);

                    if (l || r){
                        driveMotors(0, 0);
                        // We can move on
                        curPhase = TRIP_INTER;
                        return;
                    }
                    tapeFollower->step();
                    break;
                }

                case TRIP_INTER:
                {
                    // Turn until we trip the intersection detectors
                    if (destDir == World::DirL) {
                        // turning left
                        bool l = readQRD(IDLF, true);
                        if (l) {
                            driveMotors(0, 0);
                            // We tripped, move on
                            curPhase = TRIP_FOLLOW;
                            return;
                        }

                        driveMotors(-speed, speed);
                    }
                    else if (destDir == World::DirR) {
                        // turning right
                        bool r = readQRD(IDRF, true);
                        if (r) {
                            driveMotors(0, 0);
                            // We tripped, move on
                            curPhase = TRIP_FOLLOW;
                            return;
                        }
                        driveMotors(speed, -speed);
                    }
                    break;
                }

                case TRIP_FOLLOW:
                {
                    //Debug::serialPrint("Intersect turn til trip tapefollow.", Debug::INTERSECT_DB);
                    // Turn until we trip the tape followers
                    if (destDir == World::DirL) {
                        // Check if we trip the TF
                        bool l = readQRD(TFLF, true);
                        if (l) {
                            driveMotors(0, 0);
                            //Gottem we are done
                            curPhase = END;
                            return;
                        }
                        else {
                            driveMotors(-speed, speed);
                        }

                    }
                    else if (destDir == World::DirR) {
                        // Check if we trip the TF
                        bool r = readQRD(TFRF, true);
                        if (r) {
                            //Gottem we are done
                            driveMotors(0, 0);
                            curPhase = END;
                            return;
                        }
                        else {
                            driveMotors(speed, -speed);
                        }
                    }
                    break;
                }

                case END:
                {
                    //DONE:
                    driveMotors(0, 0);
                    finishIntersect();
                    break;
                }
            }
        }
    }
}
