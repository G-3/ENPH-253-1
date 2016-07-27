#include "Pickup.h"
#include "../LLRobot.h"
#include "../EHandler.h"
#include <phys253.h>

using namespace LLRobot::Rel;

namespace Control{
    namespace{

    }

    Pickup::Pickup(LLRobot::Side side,Phase phase){
        currentPhase = phase;
        currentSide = side;
        if (side == LLRobot::RIGHT){
            claw = CR;
            arm = AR;
            at = ATR;
            fS = IRRF;
            mS = IRRM;
            bS = IRRB;
        }
        else{
            claw = CL;
            arm = AL;
            at = ATL;
            fS = IRLF;
            mS = IRLM;
            bS = IRLB;
        }

    }

    Pickup::~Pickup(){
    }

    void Pickup::updatePValues(int16_t value){
        currentPointer++;
        currentPointer %= pValuesSize;
        pValues[currentPointer] = value;
    }
    
    int16_t Pickup::readPValue(int16_t stepsBack){
        int16_t val = currentPointer-stepsBack % pValuesSize;
        if (val < 0){
            val += pValuesSize;
        }
        return pValues[val];

    }

     
    void Pickup::setup(){
        openClaw(claw,true);
        extendArm(arm,false);
        driveMotors(0,0);
        LLRobot::setControlLock(true);
        if(setCurrentQSD(mS,true)){
            driveMotors(motorAmplitude,-motorAmplitude);
            currentPhase = ALIGMENT;
        }
    }
    void Pickup::alignment(){
        if (aligmentTimestamp  == 0){
            aligmentTimestamp = micros();
        }

        if (aligmentTimestamp - micros() > 3000){
            int16_t reading = readCurrentQSD(true);
            setCurrentQSD(mS,true);
            aligmentTimestamp = micros();
            //Update Previous Values
            updatePValues(reading);
            //Update Maximum Amplitude
            Serial.println(reading);
            if (reading > maxAmp)
                maxAmp = reading;
            

            //Check that a couple of previous values are all below the threshold
            if (motorAmplitude > 30){
                bool islower = true;
                for (int16_t i = 0;i < pValuesSize;i++){
                    //Serial.println("-----");
                    //Serial.println(reading);
                    //Serial.println(maxAmp);
                    //Serial.println(readPValue(i) + THRESHOLD);
                    //Serial.println("-----");
                    islower &= (readPValue(i) + THRESHOLD) < maxAmp;
                }
                
                //If the read amplitude is deacreasing, flip directions and lower motor amplitude
                if(islower){
                    motorAmplitude -= motorStepDown;

                    //flip direction
                    motorDirection = !motorDirection;
                    if (motorDirection)
                        driveMotors(motorAmplitude,-motorAmplitude);
                    else {
                        driveMotors(-motorAmplitude,motorAmplitude);
                    }

                    //reset maxAmp
                    maxAmp = reading; 



                }
            }
            else{
                //robot is aligned move to next phase
                currentPhase = EXTENSION;
            }
        }
        if ((micros() - aligmentTimestamp) > ALIGMENT_T){
            currentPhase = FAIL;
        }
    }
    void Pickup::extension(){
        //Initialize timestamp
        if (extensionTimestamp == 0){
            extensionTimestamp = millis();
            driveMotors(0,0);
        }

        if (((millis() - extensionTimestamp)/SERVO_RATE > 180)){
            currentPhase = FAIL;
        }

        //if collision has occured
        if (readArmTrip(at)){
            currentPhase = CLOSE;
        }
        else{
            uint16_t angle = (millis() - extensionTimestamp)/SERVO_RATE;
            extendArm(arm,angle);
        }
        
    }

    void Pickup::close(){
        if (clawTimestamp == 0){
            clawTimestamp = millis();
        }
        openClaw(claw,false);
        if ((millis()-clawTimestamp) > CLAW_DELAY){
            currentPhase = RETRACTION;
        }
    }
    void Pickup::retraction(){
        if (retractionTimestamp == 0){
            retractionTimestamp = millis();
        }
        int16_t angle = 70-(millis()-retractionTimestamp)/SERVO_RATE;

        if (angle >= 0){
            extendArm(arm,angle);
        }
        else{
            setPassengerPickup(claw,true);
            LLRobot::setControlLock(false);
            currentPhase = REFIND_TAPE;
        }
    }
    void Pickup::fail(){
        if (retractionTimestamp == 0){
            retractionTimestamp = millis();
        }
        int16_t angle = 70-(millis()-retractionTimestamp)/SERVO_RATE;

        if (angle >= 0){
            extendArm(arm,angle);
        }
        else{
            setPassengerPickup(claw,false);
            LLRobot::setControlLock(false);
            currentPhase = REFIND_TAPE;
        }
    }

    void Pickup::refindTape(){
        if (readQRD(TFLF) || readQRD(TFRF)){
            driveMotors(0,0);
            EHandler::finishPickup();
        }
        else{
            if (motorDirection)
                driveMotors(motorAmplitude,-motorAmplitude);
            else {
                driveMotors(-motorAmplitude,motorAmplitude);
            }
        }

        if (readQRD(IDLF) || readQRD(IDRF)){
            motorDirection = !motorDirection;
        }
    }

    void Pickup::step(){
        switch(currentPhase){
            case SETUP:
                Serial.println("Setup");
                setup();
                break;
            case ALIGMENT:
                Serial.println("Aligment");
                alignment();
                break;
            case EXTENSION:
                Serial.println("Extension");
                extension();
                break;
            case CLOSE:
                close();
                break;
            case RETRACTION:
                retraction();
                break;
            case FAIL:
                fail();
                break;
            case REFIND_TAPE:
                refindTape();
                break;
        }
    }

}

