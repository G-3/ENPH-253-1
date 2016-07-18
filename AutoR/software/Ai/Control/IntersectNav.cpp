#include "IntersectNav.h"

#include "TapeFollow.h"
#include "../World.h"
#include "../LLRobot.h"
#include "../EHandler.h"

#include <Arduino.h>
#include "../Debug.h"

using namespace LLRobot::Rel;
using namespace EHandler;

namespace Control{
    /*
     * Tape Following Mode
     */
    IntersectNav::IntersectNav(World::Node *start, World::Node *base, World::Node *dest): start(start), dest(dest), base(base){
        tapeFollower = new TapeFollow();
        speed = 100;
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

    //TODO remove knob controls from controller.

    // Note error is defined in the x direction with a robot to the right
    // of the tape having positive error.
    void IntersectNav::step(){
        bool xl = expectTapeDir[World::DirL];
        bool xr = expectTapeDir[World::DirR];
        bool xf = expectTapeDir[World::DirF];
        bool xlr = xl && xr;

		switch (curPhase) {
			case INIT_ALIGN:
			{
                Debug::serialPrint("Intersect initial align.", Debug::INTERSECT_DB);
				// Align the intersection detectors after detection 
				bool l = readQRD(IDLF, true);
				bool r = readQRD(IDRF, true);

				if (!(xl || xr)) {
                    // Just a straight intersection
					if (l || r) {
						// This wasn't supposed to happen
						// we weren't expecting a cross edge

					}
				}
				if (xlr) {
                    // Expecting left and right intersections.
					// gotta rotate until it aligns
					// need some state of what we've seen maybe
				}
				else if (l && r) {
					// Only one was supposed to be tripped
				}
				else if ((xl && l) || (xr && r)) {
					// we are good let's move on
					curPhase = DRIVE_THRU;
					return;
				}
				else if (l || r) {
					// We messed up, trip on an unexpected side
				}
				else {
					//Precondition not matched, we aren't actually on tape
				}
				break;
			}

			case DRIVE_THRU:
			{
                Debug::serialPrint("Intersect drive through.", Debug::INTERSECT_DB);
				// Drive until we activate our aligners
				// Read the alligners
				bool l = readQRD(INL, true);
				bool r = readQRD(INR, true);

				if (xlr) {
					if (l || r) {
						curPhase = INTER_ALIGN;
						return;
					}
				}

				else if (xr) {
					// only right should be tripped
					if (r) {
						curPhase = TRIP_INTER;
						return;
					}
					else if (l) {
						// expected only on the right
						//falseIntersect();
					}

				}

				else if (xl) {
					// only left should be tripped
					if (l) {
						curPhase = TRIP_INTER;
						return;
					}
					else if (r) {
						// expected only on the left
						falseIntersect();
					}
				}
				driveMotors(speed, speed);
				break;
			}

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

			case TRIP_INTER:
                Debug::serialPrint("Intersect turn til trip intersect.", Debug::INTERSECT_DB);
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
				else {
					//What?
				}
				break;
			}

			case TRIP_FOLLOW:
			{
                Debug::serialPrint("Intersect turn til trip tapefollow.", Debug::INTERSECT_DB);
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
						driveMotors(speed, -speed);
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
						driveMotors(-speed, speed);
					}
				}
				break;
			}

			case END:
			{
                Debug::serialPrint("END.", Debug::INTERSECT_DB);
				// Call da event handler
				break;
			}
		}
    }
}
