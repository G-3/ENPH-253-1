#include "TurnAround.h"
#include "PidControl.h"
#include "../LLRobot.h"
#include "../EHandler.h"
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
                driveMotors(-120, -120);
                delay(50);
                currentPhase = FIND_LEFT;
                LLRobot::flip();
                timestamp = millis();
                break;
            case FIND_LEFT:
                driveMotors(-ROTATION_SPEED,ROTATION_SPEED);
                if(readQRD(TFLF) || readQRD(TFRF)){
                    EHandler::finishTurnAround(); 
                    currentPhase = SETUP;
                    //TODO: inform event handler that we have turned around
                }
                if( readQRD(IDRF) || (millis() - timestamp > TIMEOUT_MILLIS) ){
                    currentPhase = FIND_RIGHT;
                    timestamp = millis();
                }
                break;

            case FIND_RIGHT:
                driveMotors(ROTATION_SPEED,-ROTATION_SPEED);
                if(readQRD(TFRF) || readQRD(TFLF)){
                    EHandler::finishTurnAround(); 
                    currentPhase = SETUP;
                    //TODO: inform event handler that we have turned around
                }
                if( readQRD(IDLF) || (millis() - timestamp > TIMEOUT_MILLIS) ){
                    currentPhase = FIND_LEFT;
                    timestamp = millis();
                }
                break;

            default:
                currentPhase = SETUP;
        }
    }
}
