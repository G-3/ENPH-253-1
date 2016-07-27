#include "IntersectNav.h"

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
    IntersectNav::IntersectNav(World::Node *start, World::Node *base, World::Node *dest): start(start), dest(dest), base(base){
        tapeFollower = new TapeFollow2(17,25,60);
        speed = 50;
        curPhase = INIT_ALIGN;
        base->relLinkDirs(expectTapeDir, start);
        destDir = base->relDestDir(dest, start);
       
        Debug::serialPrint("Direction . Exp Tape \n", Debug::INTERSECT_DB);
        for(int i = 0; i < 4; i++){
            char msg[20];
            sprintf(msg, "%d . %d \n", i, expectTapeDir[i]);
            Debug::serialPrint(msg, Debug::INTERSECT_DB);
        }
        char msg[20];
        sprintf(msg, "Dest Dir %d \n", destDir);
        Debug::serialPrint(msg, Debug::INTERSECT_DB);
    }

    IntersectNav::~IntersectNav(){
       delete tapeFollower; 
    }
   
    bool IntersectNav::checkMismatch(bool completed){
        // Critical Failure: Seen a direction that wasn't expected 
        if(!expectTapeDir[World::DirR] && seenTapeDir[World::DirR]){
            return true;
        }
        else if(!expectTapeDir[World::DirL] && seenTapeDir[World::DirL]){
            return true;
        }
        else if(!expectTapeDir[World::DirF] && seenTapeDir[World::DirF]){
            return true;
        }
        // Completion: We have seen all the intersections we were supposed to
        else if(    (expectTapeDir[World::DirR] == seenTapeDir[World::DirR]) &&
                    (expectTapeDir[World::DirL] == seenTapeDir[World::DirL]) &&
                    (expectTapeDir[World::DirF] == seenTapeDir[World::DirF]) )
        {
            return false;
        }
        // Incomplete: We are missing some intersections
        else{
            // return true, if we completed the intersection but still missing
            // return false, if we have not completed the intersection yet
            return completed;
        }
    }

    //TODO remove knob controls from controller.

    // Note error is defined in the x direction with a robot to the right
    // of the tape having positive error.
    void IntersectNav::step(){
        bool xl = expectTapeDir[World::DirL];
        bool xr = expectTapeDir[World::DirR];
        bool xf = expectTapeDir[World::DirF];
        bool xlr = xl && xr;
        

        // we are looking to travel forward, follow tape while tracking the intersection
        // there should be at least one other direction
        /*if (destDir == World::DirF){

            // TODO: Hack assume the forward direction has been confirmed by bot, need to check for this somehow
            seenTapeDir[World::DirF] = true;
            
            switch(curPhase){
                case INIT_ALIGN:
                {
                    // Align the intersection detectors after detection 
                    bool l = readQRD(IDLF, true);
                    bool r = readQRD(IDRF, true);
                    
                    // Update the seen tape directions
                    seenTapeDir[World::DirR] |= r;
                    seenTapeDir[World::DirL] |= l;
                    
                    // Tapefollow until we hit a correct intersection
                    if (checkMismatch(false)) {
                        // FAIL: mismatched intersection
                    }
                    else if (l || r){
                        curPhase = DRIVE_THRU;
                    }
                    tapeFollower->step();
                    break;
                }

                case DRIVE_THRU:
                {
                    if(xlr){
                        // Keep updating to find the other one
                        bool l = readQRD(IDLF, true);
                        bool r = readQRD(IDRF, true);
                        // Update the seen tape directions
                        seenTapeDir[World::DirR] |= r;
                        seenTapeDir[World::DirL] |= l;
                    }

                    // Check our aligners
                    bool l = readQRD(INL, true);
                    bool r = readQRD(INR, true);

                    if (l || r){
                        // We should have completely checked out the intersection
                        if(checkMismatch(true)){
                            // FAIL: mismatched interseciton
                        }
                        else{
                            // We are done
                            curPhase = END;
                        }
                    }
                    tapeFollower->step();
                    break;
                }

                case END:
                    // Call Eventhandler
                    // DONE:
                    finishIntersect();
                    break;
            }
        }*/

        // Turning right or left with no tape to follow
        //else 
        if(true){//!xf){
            switch(curPhase){
                // TODO: We are assuming that forward doesn't exist, need to check for this somehow
                case INIT_ALIGN:
                {
                    driveMotors(0,0);
//                    Debug::serialPrint("INIT.", Debug::INTERSECT_DB);
                    bool l = readQRD(IDLF, true);
                    bool r = readQRD(IDRF, true);
                    //Serial.print("TFL:"); Serial.println(l); 
                    //Serial.print("TFR:"); Serial.println(r); 
                    // Update the seen tape directions
                    seenTapeDir[World::DirR] |= r;
                    seenTapeDir[World::DirL] |= l;
                    
                    // Tapefollow until we hit a correct intersection
                    //if (checkMismatch(false)) {
                        // FAIL:
                        //Serial.println("Failed mismatch check");
                    //}
                    if (true){//l || r){
                        //Serial.println("Switched to Drive Thru");
                        curPhase = DRIVE_THRU;
                    }
                    break;
                }

                case DRIVE_THRU:
                {
                    driveMotors(speed, speed);
//                    Debug::serialPrint("DRIVE_THRU.", Debug::INTERSECT_DB);
                    if(xlr){
                        // Keep updating to find the other one
                        bool l = readQRD(IDLF, true);
                        bool r = readQRD(IDRF, true);
                        // Update the seen tape directions
                        seenTapeDir[World::DirR] |= r;
                        seenTapeDir[World::DirL] |= l;
                    }

                    // Check our aligners
                    bool l = readQRD(INL, true);
                    bool r = readQRD(INR, true);
                    //Serial.print("INL:"); Serial.println(l); 
                    //Serial.print("INR:"); Serial.println(r); 

                    if (l || r){
                        // We should have completely checked out the intersection
                        //if(checkMismatch(true)){
                            // FAIL:
                            //Serial.println("Failed completed mismatch check");
                        //}
                        //else{
                            // We can move on
                            // TODO: See if we can get away with this in all cases
                        curPhase = TRIP_INTER;
                        //Serial.println("Trip_inter");
                        driveMotors(0, 0);
                        //}
                    }
                    break;
                }
                
                /*
                case INTER_ALIGN:
                {
                    Debug::serialPrint("Intersect center intersection align.", Debug::INTERSECT_DB);
                    // Align the intersection aligners
                    if (!xlr) {
                        // What are we doing?
                    }
                    else {
                        //Some state stuff
                    }
                    break;
                */

                case TRIP_INTER:
                {
//                    Debug::serialPrint("TURN_INTER", Debug::INTERSECT_DB);
                    // Turn until we trip the intersection detectors
                    if (destDir == World::DirL) {
                        driveMotors(-speed, speed);
                        // turning left
                        bool l = readQRD(IDLF, true);
                        //Serial.print("L: "); Serial.println(l);
                            if (l) {
                                // We tripped, move on
                                //Serial.println("Trip inter"); 
                                curPhase = TRIP_FOLLOW;
                            }

                    }
                    else{//(destDir == World::DirR) {
                        driveMotors(speed, -speed);
                        // turning right
                        bool r = readQRD(IDRF, true);
                        // Serial.print("R: "); Serial.println(r);
                        if (r) {
                        // We tripped, move on
                            curPhase = TRIP_FOLLOW;
                            // Serial.println("Trip inter"); 
                        }
                    }
                    break;
                }

                case TRIP_FOLLOW:
                {
//                    Debug::serialPrint("TURN_TF.", Debug::INTERSECT_DB);
                    // Turn until we trip the tape followers
                    if (destDir == World::DirL) {
                        // Check if we trip the TF
                        bool l = readQRD(TFLF, true);
                        //Serial.print("L: "); Serial.println(l);
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
                    else{ //if (destDir == World::DirR) {
                        // Check if we trip the TF
                        bool r = readQRD(TFRF, true);
                        //Serial.print("R: "); Serial.println(r);
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
//                    Debug::serialPrint("END.", Debug::INTERSECT_DB);
                    driveMotors(0, 0);
                    //DONE:
                    finishIntersect();
                    break;
                }
            }
        }

        // Turn at the intersection and there is a follow through path
        else{
            // TODO: currently assumes front exists
            seenTapeDir[World::DirF] = true;
            switch (curPhase) {
                case INIT_ALIGN:
                {
                    //Debug::serialPrint("Intersect initial align.", Debug::INTERSECT_DB);
                    bool l = readQRD(IDLF, true);
                    bool r = readQRD(IDRF, true);
                    
                    // Update the seen tape directions
                    seenTapeDir[World::DirR] |= r;
                    seenTapeDir[World::DirL] |= l;
                    
                    // Tapefollow until we hit a correct intersection
                    //if (checkMismatch(false)) {
                        // FAIL:
                    //}
                   // else 
                    if (l || r){
                        curPhase = DRIVE_THRU;
                    }

                    tapeFollower->step();
                    break;
                }

                case DRIVE_THRU:
                {
                    //Debug::serialPrint("Intersect drive through.", Debug::INTERSECT_DB);
                    if(xlr){
                        // Keep updating to find the other one
                        bool l = readQRD(IDLF, true);
                        bool r = readQRD(IDRF, true);
                        // Update the seen tape directions
                        seenTapeDir[World::DirR] |= r;
                        seenTapeDir[World::DirL] |= l;
                    }

                    // Check our aligners
                    bool l = readQRD(INL, true);
                    bool r = readQRD(INR, true);

                    if (l || r){
                        // We should have completely checked out the intersection
                        //if(checkMismatch(true)){
                            // FAIL:
                        //}
                        //else{
                            // We can move on
                            if(xlr){
                                if(l) linedUp = World::DirL;
                                else if(r) linedUp = World::DirR;
                                curPhase = INTER_ALIGN;
                            }
                            else{
                                curPhase = TRIP_INTER;
                            }
                        //}
                    }
                    tapeFollower->step();
                    break;
                }

                case INTER_ALIGN:
                {
                    //Debug::serialPrint("Intersect center intersection align.", Debug::INTERSECT_DB);
                    // Align the intersection aligners
                    if (linedUp == World::DirL) {
                        // turning left
                        bool r = readQRD(INR, true);
                            if (r) {
                                // We tripped, move on
                                curPhase = TRIP_FOLLOW;
                            }

                        driveMotors(0, speed);
                    }
                    else if (linedUp == World::DirR) {
                        // turning right
                        bool l = readQRD(INL, true);
                            if (l) {
                                // We tripped, move on
                                curPhase = TRIP_FOLLOW;
                            }
                        driveMotors(speed, 0);
                    }
                    break;
                }

                case TRIP_INTER:
                {
                    //Debug::serialPrint("Intersect turn til trip intersect.", Debug::INTERSECT_DB);
                    // Turn until we trip the intersection detectors
                    if (destDir == World::DirL) {
                        // turning left
                        bool l = readQRD(IDLF, true);
                            if (l) {
                                // We tripped, move on
                                curPhase = TRIP_FOLLOW;
                            }

                        driveMotors(speed, -speed);
                    }
                    else if (destDir == World::DirR) {
                        // turning right
                        bool r = readQRD(IDRF, true);
                            if (r) {
                                // We tripped, move on
                                curPhase = TRIP_FOLLOW;
                            }
                        driveMotors(-speed, speed);
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
                    //Debug::serialPrint("END.", Debug::INTERSECT_DB);
                    //DONE:
                    finishIntersect();
                    break;
                }
            }
        }
    }
}
