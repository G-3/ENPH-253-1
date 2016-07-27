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

    }

    DropOff::~DropOff(){
    }

    void DropOff::setup(){
        Claw altClaw;
        Arm altArm;
        if (side == LLRobot::RIGHT){
            altClaw = CL;
            altArm = AR;
            claw = CR;
            arm = AR;
        }
        else{
            altClaw = CR;
            altArm = AR;
            claw = CL;
            arm = AL;
        }
        if (getPassengerPickup(claw)){
            currentPhase = EXTENSION;
        }

        else if (getPassengerPickup(altClaw)){
                claw = altClaw;
                arm = altArm;
        }
        else{
            //TODO:Event Handler screwed up
        }
    }
    void DropOff::oneEightyP1(){
        driveMotors(-50,50);
        if(readQRD(IDLF)){
           currentPhase = ONE_EIGHTY_P2; 
        }
    }
    void DropOff::oneEightyP2(){
        driveMotors(-40,40);
        if( readQRD(TFLF) || readQRD(TFLF) ){
           currentPhase = EXTENSION; 
           //TODO: inform event handler that we have flipped orientations
        }
        
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
            setPassengerPickup(claw,false);
            if (getPassengerPickup(CL)||getPassengerPickup(CR)){
                //if there is still another animal try again
                currentPhase = SETUP;
            }
            else{
                //TODO: Call back to event handler informing that drop-off is done
            }
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
