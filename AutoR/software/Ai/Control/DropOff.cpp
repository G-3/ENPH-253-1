#include <phys253.h>

#include "DropOff.h"
#include "../LLRobot.h"
#include "../EHandler.h"

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
            LLRobot::flip();
            currentPhase = ONE_EIGHTY_P1;
        }
        else{
            //TODO:Event Handler screwed up
        }
    }
    void DropOff::oneEightyP1(){
        driveMotors(-140,140);
        if(readQRD(IDLF) > 250){
           currentPhase = ONE_EIGHTY_P2; 
        }
    }
    void DropOff::oneEightyP2(){
        driveMotors(-60,60);
        if( readQRD(TFLF) > 250 || readQRD(TFRF) > 250 ){
           currentPhase = EXTENSION; 
        }
        
    }

    void DropOff::extension(){

        driveMotors(0,0);
        //Initialize timestamp
        if (extensionTimestamp == 0){
            extensionTimestamp = millis();
            extendArm(arm,200);
        }

        if (millis() - extensionTimestamp > EXTENSION_DELAY){
            extensionTimestamp = 0;
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
            releaseTimestamp = 0;
            currentPhase = RETRACTION;
            setPassengerPickup(claw,false);
        }
    }

    void DropOff::retraction(){
        //Initialize timestamp
        if (retractionTimestamp == 0){
            retractionTimestamp = millis();
            extendArm(arm,0);
        }

        if (millis() - retractionTimestamp > RETRACTION_DELAY){
            retractionTimestamp = 0;
            if (getPassengerPickup(CL)||getPassengerPickup(CR)){
                //if there is still another animal try again
                currentPhase = SETUP;
            }
            else{
                //Call back to event handler informing that drop-off is done
                EHandler::finishDropOff();
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
            case ONE_EIGHTY_P1:
                oneEightyP1();
                break;
            case ONE_EIGHTY_P2:
                oneEightyP2();
                break;

        }
    }
    
}
