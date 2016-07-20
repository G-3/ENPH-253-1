#include "Pickup.h"
#include "../LLRobot.h"
#include <phys253.h>

using namespace LLRobot::Rel;

namespace Control{
    namespace{

    }

    Pickup::Pickup(LLRobot::Side side){
        currentPhase = SETUP;
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
        currentPhase = ALIGMENT;
        LLRobot::setControlLock(true);
        setCurrentQSD(mS,true);
        
        driveMotors(motorAmplitude,-motorAmplitude);
    }
    void Pickup::alignment(){
        int16_t val = readCurrentQSD(mS,true);

        //Update Maximum Amplitude
        if (val > maxAmp)
            maxAmp = val;
        

        //Check that a couple of previous values are all below the threshold
        if (motorAmplitude > 40){
            bool islower = true;
            for (int16_t i = 0;i < pValuesSize;i++){
                if (readPValue(i) + THRESHOLD > maxAmp){
                    islower = false;
                }
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
                maxAmp = val; 



            }
            
        }
        else{
            //robot is aligned move to next phase
            currentPhase = EXTENSION;
        }

        updatePValues(val);
    }
    void Pickup::extension(){
        //Initialize timestamp
        if (extensionTimestamp == 0){
            extensionTimestamp = millis();
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
        if ((millis()-clawTimestamp) > CLAW_DELAY)
            currentPhase = RETRACTION;
    }
    void Pickup::retraction(){
        extendArm(arm,0);
        //TODO: Callback and inform event handler that pickup is complete 
        LLRobot::setControlLock(false);
    }

    void Pickup::step(){
        switch(currentPhase){
            case SETUP:
                setup();
                break;
            case ALIGMENT:
                alignment();
                break;
            case EXTENSION:
                extension();
                break;
            case CLOSE:
                close();
                break;

            case RETRACTION:
                retraction();
                break;
        }
    }

}

