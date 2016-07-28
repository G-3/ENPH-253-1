#include "../LLRobot.h"
#include <phys253.h>
#include "TapeFollow2.h"
#include "../HLRobot.h"
using namespace LLRobot::Rel;
namespace Control{
    TapeFollow2::TapeFollow2(int16_t dGain, int16_t pGain, int16_t base){
        this->base = base;
        this->dGain = dGain;
        this->pGain = pGain;
        transitionTime = 0;
        timestamp = 0;
    }
    TapeFollow2::~TapeFollow2(){
    }
    void TapeFollow2::step(){
        int sensorL = LLRobot::Rel::readQRD(LLRobot::Rel::TFLF, false);
        int sensorR = LLRobot::Rel::readQRD(LLRobot::Rel::TFRF, false);
        
        int32_t time = millis();
        int16_t right = base;
        int16_t left = base;
        if (currentSide == LLRobot::RIGHT){
            //Serial.println("right");
            if (sensorL < THLD_RIGHT && sensorR < THLD_LEFT){
                //tape lost
                left = base - pGain*2;
                right = base + pGain*2;
            }
            else if (sensorL + HYSTERESIS < sensorR){
                //transition detected to the left side
                left = base + dGain + pGain;
                right = base - dGain - pGain;

                //restimate transition time
                transitionTime = time-timestamp;
                timestamp = time;

                //switch sides
                currentSide = LLRobot::LEFT;
            }
            else{
                if (time > timestamp+transitionTime){
                    //Serial.println("00000000");
                    left = base - pGain;
                    right = base + pGain;
                }
                else if (time > (timestamp+transitionTime/2)){
                    //Serial.println("--------");
                    left = base + dGain - pGain;
                    right = base - dGain + pGain;
                }
                else{
                    //Serial.println("++++++++");
                    left = base - dGain - pGain;
                    right = base + dGain + pGain;
                }
            }
        }
        else{
            //Serial.println("left");
            if (sensorL < THLD_RIGHT && sensorR < THLD_LEFT){
                //tape lost
                left = base + pGain*2;
                right = base - pGain*2;
            }
            else if (sensorR + HYSTERESIS < sensorL){
                //transition detected to the right side
                left = base - dGain - pGain;
                right = base + dGain + pGain;

                //restimate transition time
                transitionTime = time-timestamp;
                timestamp = time;

                //switch sides
                currentSide = LLRobot::RIGHT;
            }
            else{
                if (time > timestamp+transitionTime){
                    //Serial.println("00000000");
                    left = base + pGain;
                    right = base - pGain;
                }
                else if (time > (timestamp+transitionTime/2)){
                    //Serial.println("--------");
                    left = base - dGain + pGain;
                    right = base + dGain - pGain;
                }
                else{
                    //Serial.println("++++++++");
                    left = base + dGain + pGain;
                    right = base - dGain - pGain;
                }
            }
        }
        //Serial.println(left);
        //Serial.println(right);
        //Serial.println(base);
        driveMotors(left,right);
    }
}
