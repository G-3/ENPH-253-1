#include <phys253.h>

#include "DropOff.h"
#include "../LLRobot.h"

using namespace LLRobot::Rel;

namespace Control{
    DropOff::DropOff(LLRobot::Side side){
        currentPhase = SETUP;
        extensionTimestamp = 0;
        releaseTimestamp = 0;
        retractionTimestamp = 0;

        if (side == LLRobot::RIGHT){
            claw = CR;
            arm = AR;
        }
        else{
            claw = CL;
            arm = AL;
        }
    }

    DropOff::~DropOff(){
    }

    void DropOff::setup(){
        currentPhase = EXTENSION;
    }

    void DropOff::extension(){
        //Initialize timestamp
        if (extensionTimestamp == 0){
            extensionTimestamp = millis();
            extendArm(arm,200);
        }

        if (millis() - extensionTimestamp > EXTENSION_DELAY){
            currentPhase = RELEASE;
        }
    }

    void DropOff::release(){
        //Initialize timestamp
        if (releaseTimestamp == 0){
            releaseTimestamp = millis();
            openClaw(claw,true);
        }

        if (millis() - releaseTimestamp > RELEASE_DELAY){
            currentPhase = RETRACTION;
        }
    }

    void DropOff::retraction(){
        //Initialize timestamp
        if (retractionTimestamp == 0){
            retractionTimestamp = millis();
            extendArm(arm,0);
        }

        if (millis() - retractionTimestamp > RETRACTION_DELAY){
            //TODO: Call back to event handler
        }
    }

    void DropOff::step(){
        switch(currentPhase){
            case SETUP:    
                setup();
                break;
            case EXTENSION:
                extension();
                break;
            case RELEASE: 
                release();
                break;
            case RETRACTION:
                retraction();
                break;
        }
    }
    
}
