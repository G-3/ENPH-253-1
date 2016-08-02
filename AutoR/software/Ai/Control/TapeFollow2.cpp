#include "../LLRobot.h"
#include <phys253.h>
#include "TapeFollow2.h"
#include "../HLRobot.h"
using namespace LLRobot::Rel;
namespace Control{
    TapeFollow2::TapeFollow2(int16_t dGain, int16_t pGain, int16_t base,int16_t iGain, int16_t eBase,int16_t eGain,int16_t hysteresis){
        this->base = base;
        this->dGain = dGain;
        this->pGain = pGain;
        this->iGain = iGain;
        this->eGain = eGain;
        this->eBase = eBase;
        this->hysteresis = hysteresis;
        transitionTimeRight = 0;
        transitionTimeLeft = 0;
        timestamp = 0;
        integral = 0;
    }
    TapeFollow2::~TapeFollow2(){
    }
    void TapeFollow2::step(){
        int sensorL = LLRobot::Rel::readQRD(LLRobot::Rel::TFLF, false);
        int sensorR = LLRobot::Rel::readQRD(LLRobot::Rel::TFRF, false);
        bool idlf = LLRobot::Rel::readQRD(LLRobot::Rel::IDLF, true);
        bool idrf = LLRobot::Rel::readQRD(LLRobot::Rel::IDRF, true);
        
        uint32_t time = micros();
        int16_t right = base;
        int16_t left = base;

        if (idlf){
            currentSide = LLRobot::RIGHT;
        }
        else if(idrf){
            currentSide = LLRobot::LEFT;
        }

        if (currentSide == LLRobot::RIGHT){
            //Serial.println("right");
            if (sensorL < THLD_RIGHT && sensorR < THLD_LEFT){
                //tape lost
                left = eBase - pGain*2;
                right = eBase + pGain*2;
            }
            else if (sensorL + hysteresis < sensorR){
                //transition detected to the left side
                left = base + dGain + pGain;
                right = base - dGain - pGain;

                //restimate transition time
                transitionTimeRight = time-timestamp;
                timestamp = time;

                integral += (float)transitionTimeLeft/(transitionTimeRight+transitionTimeLeft) - 0.5;

                //switch sides
                currentSide = LLRobot::LEFT;
            }
            else{
                if (time > timestamp+transitionTimeRight){
                    //Serial.println("00000000");
                    left = base - pGain;
                    right = base + pGain;
                }
                else if (time > (timestamp+transitionTimeRight/2)){
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
                left = eBase + pGain*2;
                right = eBase - pGain*2;
            }
            else if (sensorR + hysteresis < sensorL){
                //transition detected to the right side
                left = base - dGain - pGain;
                right = base + dGain + pGain;

                //restimate transition time
                transitionTimeLeft = time-timestamp;
                timestamp = time;

                integral += (float)transitionTimeLeft/(transitionTimeRight+transitionTimeLeft) - 0.5;

                //switch sides
                currentSide = LLRobot::RIGHT;
            }
            else{
                if (time > timestamp+transitionTimeLeft){
                    //Serial.println("00000000");
                    left = base + pGain;
                    right = base - pGain;
                }
                else if (time > (timestamp+transitionTimeLeft/2)){
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
        left -= (int16_t)(integral*iGain);
        right += (int16_t)(integral*iGain);

        if (integral > 4)
            integral = 4;
        if (integral < -4)
            integral = -4;

        driveMotors(left,right);
        
        lcdCount += 1;
        /*if(lcdCount % 20 == 0){
            LCD.clear(); LCD.home();
            LCD.print(transitionTimeRight);
            LCD.setCursor(0, 1);
            LCD.print(transitionTimeLeft);
            lcdCount = 1;
        }*/
    }
}
