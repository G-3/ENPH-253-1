#include "TapeFollow.h"
#include "PidControl.h"
#include "../LLRobot.h"
#include <phys253.h>

namespace Control{
    namespace{
        int timeFromChange = 0;
        float deltaE;
        int qTime = 50;
    }

    /*
     * Tape Following Mode
     */
    TapeFollow::TapeFollow(){
        controlProcess = new PidControl();
        err = dir = 0;
    }

    TapeFollow::~TapeFollow(){
       delete controlProcess; 
    }

    //TODO remove knob controls from controller.
    // Note error is defined in the x direction with a robot to the right
    // of the tape having positive error.
    void TapeFollow::step(){
        
        int sensorL = LLRobot::Rel::readQRD(LLRobot::Rel::TFLF, false);
        int sensorR = LLRobot::Rel::readQRD(LLRobot::Rel::TFRF, false);
        int diff = sensorL-sensorR; 
        int l,r;
        if (sensorL < 200) l = 0;
        else l = 1;
        if (sensorR < 200) r = 0;
        else r = 1;

        if (l == 0 && r == 0){
            //Both off
            if (dir == 0){
                err = -500;
            } else {
                err = 500;
            }
        }
        else{
            //1 on 1 off

            if (l == 0 && r == 1){
                dir = 0;
                err = -300;
            }else if(l == 1 && r == 0){
                dir = 1;
                err = 300;
            }
            if (err>0){
                dir = 1;
            }
            else{
                dir = 0;
            }


        }
        
        float derivative = 0;

        if (err != errp){
            deltaE = (float)(err - errp);
            timeFromChange = qTime;
            derivative = deltaE/timeFromChange;
        }
        else {
            timeFromChange += dt;
            derivative = deltaE/timeFromChange;
        }
        if (l == 1 && r == 1) {
            // both on 
            err = diff;
            deltaE = (float)(err - errp);
            derivative = deltaE/dt;
        }
        
        double Vc = controlProcess->step(err, derivative); 
        
		int G = knob(6) / 100;
        int base1 = knob(7)/4;
        // With a positive reaction needed, we need to increase the left motor.
        int powerL = base1 - G*Vc;
        if (powerL > 255) powerL = 255;
        if (powerL < 0) powerL = 0;

        // With a positive reaction needed, we need to decrease the right motor.
        int powerR = base1 + G*Vc;
        if (powerR > 255) powerR = 255;
        if (powerR < 0) powerR = 0;

        LLRobot::Rel::driveMotors(powerL, powerR);
        counter+=1;
	
        if(counter%30==0){
            Serial.println("~~~~~~~~~");
            Serial.println(powerR);
            Serial.println(powerL);
            Serial.println("-       -");
            Serial.println(sensorL);
            Serial.println(sensorR);
            Serial.println("~~~~~~~~~");
            Serial.println();
            counter = 0;
            LCD.clear();
            LCD.home();
            LCD.print(base1);
            LCD.print(" | ");
            LCD.print(G);
            LCD.setCursor(0,1);
            LCD.print(sensorR);
            LCD.print(" | ");
            LCD.print(sensorL);
        }
        errp = err;
    }
}
