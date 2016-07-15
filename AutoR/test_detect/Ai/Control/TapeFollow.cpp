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
        if (sensorL < THLD1) l = 0;
        else l = 1;
        if (sensorR < THLD2) r = 0;
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
        
        v = knob(7)/4.;
        // With a positive reaction needed, we need to increase the left motor.
        int powerL = base - G*Vc;
        if (powerL > 255) powerL = 255;
        if (powerL < 0) powerL = 0;

        // With a positive reaction needed, we need to decrease the right motor.
        int powerR = base + G*Vc;
        if (powerR > 255) powerR = 255;
        if (powerR < 0) powerR = 0;

        LLRobot::Rel::driveMotor(LLRobot::Rel::DML, powerL);
        LLRobot::Rel::driveMotor(LLRobot::Rel::DMR, powerR);
	counter+=1;
	
	if(counter%10==0){
	    /*jSerial.println("~~~~~~~~~");
	    Serial.println(powerR);
	    Serial.println(powerL);
	    Serial.println("-       -");
	    Serial.println(sensorL);
	    Serial.println(sensorR);
	    Serial.println("~~~~~~~~~");
	    Serial.println();  */
	    counter = 0;
	    LCD.clear();
            LCD.home();
	    LCD.print(sensorL);
	    LCD.print(" | ");
	    LCD.print(powerL);
	    LCD.setCursor(0,1);
	    LCD.print(sensorR);
	    LCD.print(" | ");
	    LCD.print(Vc);
	}
        errp = err;
	delay(dt);
    }
}
