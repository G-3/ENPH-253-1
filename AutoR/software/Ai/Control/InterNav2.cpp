#include "Internav2.h"
#include "../EDetect.h"
#include "../EHandler.h"
#include "../World.h"
#include <phys253.h>
using namespace LLRobot::Rel;
namespace Control{
            InterNav2::InterNav2(bool expectedTapeDir[],World::Dir direction,int16_t ss1,int16_t ss2,int16_t ds){
                xl = expectedTapeDir[World::DirL];
                xr = expectedTapeDir[World::DirR];
                xf = expectedTapeDir[World::DirF];
                this->direction = direction;
                tapeFollower = new TapeFollow2(17,25,ds);
                driveSpeed = ds;
                spinSpeed1 = ss1;
                spinSpeed2 = ss2;
            }

            InterNav2::~InterNav2(){
                delete tapeFollower;
            }
            void InterNav2::setup(){
                currentPhase = ALIGN_NAVIGATORS;
            }
            void InterNav2::alignNavigators(){

                bool idrb = readQRD(IDRB,true);
                bool idlb = readQRD(IDLB,true);
                bool inl = readQRD(INL,true);
                bool inr = readQRD(INR,true);

                motorDirection |= (idrb || idlb);
                Serial.println(motorDirection);
                int16_t ds = motorDirection ? -driveSpeed : driveSpeed;

                switch(direction){
                    case World::DirR:
                        driveMotors(ds,ds);
                        if (inr){
                            currentPhase = TURN_P1;
                        }
                        break;
                    case World::DirL:
                        driveMotors(ds,ds);
                        if (inl){
                            currentPhase = TURN_P1;
                        }
                        break;
                    case World::DirF:
                        if (inr || inl){
                            currentPhase = GO_STRAIGHT;
                        }
                        //driveMotors(ds,ds);
                        tapeFollower->step();
                        break;
                }
            }
            void InterNav2::turnPhase1(){
                bool idrf = readQRD(IDRF,true);
                bool idlf = readQRD(IDLF,true);
                switch(direction){
                    case World::DirR:
                        driveMotors(spinSpeed1,-spinSpeed1);
                        if (idrf){
                            currentPhase = TURN_P2;
                        }
                        break;
                    case World::DirL:
                        driveMotors(-spinSpeed1,spinSpeed1);
                        if (idlf){
                            currentPhase = TURN_P2;
                        }
                        break;
                }
            }
            void InterNav2::turnPhase2(){
                bool tfrf = readQRD(TFRF,true);
                bool tflf = readQRD(TFLF,true);
                switch(direction){
                    case World::DirR:
                        driveMotors(spinSpeed2,-spinSpeed2);
                        break;
                    case World::DirL:
                        driveMotors(-spinSpeed2,spinSpeed2);
                        break;
                }
                if (tflf || tfrf){
                    currentPhase = EXIT_INTER;
                }

            }
            void InterNav2::goStraight(){
                bool inrf = readQRD(INR,true);
                bool inlf = readQRD(INL,true);
                tapeFollower->step();
                if (inrf || inlf){
                    currentPhase = EXIT_INTER;
                }

            }
            void InterNav2::exitInter(){
                tapeFollower->step();
                bool doneIntersection = false;
                Serial.println(readQRD(IDRB));
                Serial.println(readQRD(IDLB));
                bool idrb = readQRD(IDRB,false) > 150;
                bool idlb = readQRD(IDLB,false) > 150;
                switch(direction){
                    case World::DirR:
                        doneIntersection = idrb;
                        break;
                    case World::DirL:
                        doneIntersection = idlb;
                        break;
                    case World::DirF:
                        //Wait for both intersection detectors to go off;
                        rightBackTrip |= idrb; 
                        leftBackTrip |= idrb;
                        doneIntersection = (rightBackTrip && leftBackTrip);
                        break;
                }
                if (doneIntersection){

                    LCD.clear();LCD.home();
                    LCD.print("Done!");
                    EHandler::finishIntersect();
                }
                Serial.println(readQRD(TFRF));
                Serial.println(readQRD(TFLF));
            }

            void InterNav2::step(){
                switch(currentPhase){
                    case SETUP:
                        setup();
                        Serial.println("S");
                        break;
                    case ALIGN_NAVIGATORS:
                        alignNavigators();
                        Serial.println("AN");
                        break;
                    case TURN_P1:
                        turnPhase1();
                        Serial.println("TP1");
                        break;
                    case TURN_P2:
                        turnPhase2();
                        Serial.println("TP2");
                        break;
                    case GO_STRAIGHT:
                        goStraight();
                        Serial.println("GS");
                        break;
                    case EXIT_INTER:
                        Serial.println("EI");
                        exitInter();
                        break;
                }
                //checkBumpers();
            }
            void InterNav2::checkBumpers(){
                if (Event::EDetect::getInstance()->checkBumpers()){
                    //reset variables
                    leftBackTrip = false;
                    rightBackTrip = false;
                    motorDirection = false;

                    //Logically flip the robot
                    LLRobot::flip();

                    //Flip high level nodes
                    EHandler::reverseIntersect();

                    //Flip direction through an intersection
                    if (direction == World::DirR){
                        direction = World::DirL;
                    }
                    else if (direction == World::DirL){
                        direction = World::DirR;
                    }

                    switch(currentPhase){
                        case SETUP:
                            EHandler::finishIntersect();
                            break;
                        case ALIGN_NAVIGATORS:
                            EHandler::finishIntersect();
                            break;
                        case TURN_P1:
                            currentPhase = TURN_P2;
                            break;
                        case TURN_P2:
                            currentPhase = TURN_P1;
                            break;
                        case GO_STRAIGHT:
                            currentPhase = GO_STRAIGHT;
                            break;
                        case EXIT_INTER:
                            currentPhase = ALIGN_NAVIGATORS;
                            break;
                    }
                }
            }
    

}
