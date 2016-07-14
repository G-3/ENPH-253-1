#include "PidControl.h"
#include <phys253.h>

namespace Control{
    // Vc is defined as the reaction needed to counteract the error and is also
    // defined in the x direction with a robot to the right of the tape having
    // negative Vc.
    double PidControl::step(int error){
        while (startbutton()){
	    LCD.clear(); LCD.home();
	    while(!stopbutton()){
		LCD.clear();
		LCD.print("Set P = ");
		LCD.print(knob(6)/10);
                LCD.setCursor(0, 1);
		LCD.print("Prev: ");
                LCD.print(P);
		delay(50);
	    }
	    P = knob(6)/10;
	    delay(500);

	    LCD.clear(); LCD.home();
	    while(!stopbutton()){
		LCD.clear();
		LCD.print("Set I = ");
		LCD.print(knob(6)/10);
                LCD.setCursor(0, 1);
		LCD.print("Prev: ");
                LCD.print(I);
		delay(50);
	    }
	    I = knob(6)/10;
	    delay(500);

	    LCD.clear(); LCD.home();
	    while(!stopbutton()){
		LCD.clear();
		LCD.print("Set D = ");
		LCD.print(knob(6)/10);
                LCD.setCursor(0, 1);
		LCD.print("Prev: ");
                LCD.print(D);
		delay(50);
	    }
	    D = knob(6)/10;
	    delay(500);
	}

	errsum += error*dt;

        if (errsum > errsummax) errsum = errsummax;
        if (errsum < -errsummax) errsum = -errsummax;


        double Vc = -(P*error + I*errsum + D*(error - errp)/dt)/100.;

        errp = error;

        return Vc;
    }
}
