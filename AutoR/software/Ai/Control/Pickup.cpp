#include "Pickup.h"
#include "../LLRobot.h"
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
        int16_t reading = readCurrentQSD(true);
        //Update Maximum Amplitude
        if (reading > maxAmp)
            maxAmp = reading;
        

        //Check that a couple of previous values are all below the threshold
        if (motorAmplitude > 60){
            bool islower = true;
            for (int16_t i = 0;i < pValuesSize;i++){
                Serial.println("-----");
                Serial.println(reading);
                Serial.println(maxAmp);
                Serial.println(readPValue(i) + THRESHOLD);
                Serial.println("-----");
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

        updatePValues(reading);
    }
    void Pickup::extension(){
        //Initialize timestamp
        if (extensionTimestamp == 0){
            extensionTimestamp = millis();
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
        extendArm(arm,0);
        //TODO: Callback and inform event handler that pickup is complete 
        LLRobot::setControlLock(false);
    }
    void Pickup::fail(){
        extendArm(arm,0);
        //TODO: Callback and inform event handler that pickup has failed 
        LLRobot::setControlLock(false);
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
        }
    }

}

