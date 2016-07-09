#include "Controller.h"
#include "LLRobot.h"

void Controller::step(){
    followTape();
}

void Controller::followTape(){
  int sensor1 = LLRobot::readQRD(LLRobot::TFLF);
  int sensor2 = LLRobot::readQRD(LLRobot::TFRF);
  int l,r;
  if (sensor1 < THLD1) l = 0;
  else l = 1;

  if (sensor2 < THLD2) r = 0;
  else r = 1;

  //Determine the new error signal
  if (l == 0 && r == 1){
    err -= 1;
    dir = 0;
  } else if (l == 1 && r == 0){
    err += 1;
    dir = 1;
  } else if (l == 0 && r == 0){
    if (dir == 0){
      err -= 5;
    } else {
      err += 5;
    }
  } else if (l == 1 && r == 1){
    err = 0;
  }

  errsum += err*dt;

  if (errsum > errsummax) errsum = errsummax;
  if (errsum < -errsummax) errsum = -errsummax;

  G = knob(6)/100;
  v = knob(7)/4;

  Vc = G*(P*err + I*errsum + D*(err - errp)/dt);

  errp = err;

  int power1 = v*(base + Vc*dt/1000);
  if (power1 > 255) power1 = 255;
  if (power1 < 0) power1 = 0;

  int power2 = v*(base - Vc*dt/1000);
  if (power2 > 255) power2 = 255;
  if (power2 < 0) power2 = 0;


  motor.speed(motor1,power1);
  motor.speed(motor2,-1*power2);
}
