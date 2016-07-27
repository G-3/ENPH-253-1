#include "TurnAround.h"
#include "PidControl.h"
#include "../LLRobot.h"
#include <phys253.h>

using namespace LLRobot::Rel;

namespace Control{
    /*
     * Turn Around Mode
     */
    TurnAround::TurnAround(){
        currentPhase = SETUP;
    }

    TurnAround::~TurnAround(){
    }

    void TurnAround::step(){
        switch(currentPhase){
            case SETUP:
                extendArm(AL,false);
                extendArm(AR,false);
                openClaw(CL,true);
                openClaw(CR,true);
                currentPhase = FIND_LEFT;
                LLRobot::flip();
                break;
            case FIND_LEFT:
                driveMotors(-ROTATION_SPEED,ROTATION_SPEED);
                if(readQRD(TFLF) || readQRD(TFRF)){
                    currentPhase = SETUP;
                    //TODO: inform event handler that we have turned around
                }
                if(readQRD(IDLF)){
                    currentPhase = FIND_RIGHT;
                }
                break;

            case FIND_RIGHT:
                driveMotors(ROTATION_SPEED,-ROTATION_SPEED);
                if(readQRD(TFRF) || readQRD(TFLF)){
                    currentPhase = SETUP;
                    //TODO: inform event handler that we have turned around
                }
                if(readQRD(IDRF)){
                    currentPhase = FIND_LEFT;
                }
                break;

            default:
                currentPhase = SETUP;
        }
    }
}
