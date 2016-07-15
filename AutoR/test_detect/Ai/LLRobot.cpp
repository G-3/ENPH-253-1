#include "LLRobot.h"
#include <phys253.h>

namespace LLRobot{
    //All values are absolute
    const int QRD_THRESH[] = {200,200,200,200,200,200,200,200,200,200};
    const int QRD_PEAK[] = {500,500,500,500,500,500,500,500,500,500};
    const int QSD_THRESH[] = {100,100,100,50,100,100,100,50};
    const int QSD_PEAK[] = {1024,1024,1024,1024,1024,1024,1024,1024};

    namespace{
        // TODO: Add the pin placement for the back as well, maybe have a lookup table instead of enum


        // Analog In
        const int pinIAR = 5;

        enum QRDFront {pinTFLF=3,pinTFRF=2,pinIDLF=4,pinIDRF=1};
        enum QRDBack  {pinTFLB=3,pinTFRB=2,pinIDLB=4,pinIDRB=1};
        
        enum ArmValues {ExtendRight = 100, ExtendLeft = 100, RetractRight = 30, RetractLeft = 30};
        enum ClawValues {OpenRight = 100, OpenLeft = 100, CloseRight = 30, CloseLeft = 30};

        // Digital Out
        enum DOut {pinQSTReset = 4,pinMPQSD0 = 5, pinMPQSD1 = 6, pinMPQSD2 = 7, pinMPQRD=8};
        // Motor out
        enum MOut {pinDML=2, pinDMR=1};
        // Servo indicies
        enum SOut {AGL=0, AGR=1,AML=2,AMR=3};
        ServoTINAH servos[] = {RCServo0,RCServo1,RCServo2,RCServo3};
        // Digital In
        enum DIn {pinATR=8,pinATL=9,pinBF=10,pinBB=11};
        // Current Multiplexer States
        Orientation orientation = Forwards;
        bool MPQRD_state = orientation;

        //Start off with both arms retracted
        bool RightArmState = 0;
        bool LeftArmState = 0;

    }   
    
    int multiplexReadQrd(Orientation direction,int pin){
        if(MPQRD_state != direction){
            digitalWrite(pinMPQRD, direction);
            MPQRD_state = direction;
        }
        int val = analogRead(pin);
        return val;
    }
    
    namespace Abs{
        int threshQRD(QRD position){
            return QRD_THRESH[position];
        }

        int peakQRD(QRD position){
            return QRD_PEAK[position];
        }

        int threshQSD(QSD position){
            return QSD_THRESH[position];
        }

        int peakQSD(QSD position){
            return QSD_PEAK[position];
        }

        int readQRD(QRD position, bool applyThresh){
            int val = -1;
            switch(position){
                case TFLF:
                    val = multiplexReadQrd(Forwards,pinTFLF);
                    break;

                case TFRF:
                    val = multiplexReadQrd(Forwards,pinTFRF);
                    break;

                case TFLB:
                    val = multiplexReadQrd(Backwards,pinTFLB);
                    break;

                case TFRB:
                    val = multiplexReadQrd(Backwards,pinTFRB);
                    break;

                case IDLF:
                    val = multiplexReadQrd(Forwards,pinIDLF);
                    break;

                case IDRF:
                    val = multiplexReadQrd(Forwards,pinIDRF);
                    break;

                case IDLB:
                    val = multiplexReadQrd(Backwards,pinIDLB);
                    break;

                case IDRB:
                    val = multiplexReadQrd(Backwards,pinIDRB);
                    break;
                
                default:
                    return -1;
            }
            return applyThresh ? val >= threshQRD(position) : val;
        }

        int readQSD(QSD position, bool applyThresh){
            //TODO: not implemented
            return -1;
        }
       
        
        // Move the specified motor at speed 
        bool driveMotor(DMot motorpos, int16_t speed){
            switch(motorpos){
                case DML:
                    Serial.println(pinDML);
                    Serial.println(speed);
                    Serial.println("~~~~");
                    motor.speed(pinDML, speed);
                    return true;
                case DMR:
                    Serial.println(pinDMR);
                    Serial.println(-speed);
                    Serial.println("~~~~");
                    motor.speed(pinDMR, -speed);
                    return true;
            } 
            return false;
        }

        bool extendArm(Arm arm, bool pos){
            if (pos){
                switch(arm){
                    case AR:
                        servos[AMR].write(ExtendRight);
                    case AL:
                        servos[AML].write(ExtendLeft);
                }
            }
            else{
                switch(arm){
                    case AR:
                        servos[AMR].write(RetractRight);
                    case AL:
                        servos[AML].write(RetractLeft);
                }
            }

            return true;
        }

        bool openClaw(Claw claw, bool pos){
            if (pos){
                switch(claw){
                    case CR:
                        servos[CR].write(OpenRight);
                    case CL:
                        servos[CL].write(OpenLeft);
                }
            }
            else{
                switch(claw){
                    case CR:
                        servos[AMR].write(CloseRight);
                    case CL:
                        servos[AMR].write(CloseLeft);
                }
            }

            return true;
        }

        bool readArmTrip(ArmTrip armTrip){
            switch(armTrip){
                case ATR:
                    return digitalRead(pinATR);
                case ATL:
                    return digitalRead(pinATL);
            }
        }

        bool readBumper(Bumper bumper){
            switch(bumper){
                case BF:
                    return digitalRead(pinBF);
                case BB:
                    return digitalRead(pinBB);
            }
        }
    }
    
    Abs::QRD relToAbsQRD(Rel::QRD position){
        Abs::QRD newPos;
        if (orientation == Forwards){
            switch(position){
                case Rel::TFLF:
                    newPos = Abs::TFLF;
                case Rel::TFRF:
                    newPos = Abs::TFRF;
                case Rel::TFLB:
                    newPos = Abs::TFLB;
                case Rel::TFRB:
                    newPos = Abs::TFRB;
                case Rel::IDLF:
                    newPos = Abs::IDLF;
                case Rel::IDRF:
                    newPos = Abs::IDRF;
                case Rel::IDLB:
                    newPos = Abs::IDLB;
                case Rel::IDRB:
                    newPos = Abs::IDRB;
            }
        }
        else{
            switch(position){
                case Rel::TFLF:
                    newPos = Abs::TFRB;
                case Rel::TFRF:
                    newPos = Abs::TFLB;
                case Rel::TFLB:
                    newPos = Abs::TFRF;
                case Rel::TFRB:
                    newPos = Abs::TFLF;
                case Rel::IDLF:
                    newPos = Abs::IDRB;
                case Rel::IDRF:
                    newPos = Abs::IDLB;
                case Rel::IDLB:
                    newPos = Abs::IDRF;
                case Rel::IDRB:
                    newPos = Abs::IDLF;
            }
        }
        return newPos;

    }
    Abs::QSD relToAbsQSD(Rel::QSD position){
        Abs::QSD newPos;
        if (orientation == Forwards){
            switch(position){
                case Rel::IRLF:
                    newPos = Abs::IRLF;
                case Rel::IRLM:
                    newPos = Abs::IRLM;
                case Rel::IRLB:
                    newPos = Abs::IRLB;
                case Rel::IRLU:
                    newPos = Abs::IRLU;
                case Rel::IRRF:
                    newPos = Abs::IRRF;
                case Rel::IRRM:
                    newPos = Abs::IRRM;
                case Rel::IRRB:
                    newPos = Abs::IRRB;
                case Rel::IRRU:
                    newPos = Abs::IRRU;
            }
        }
        else{
            switch(position){
                case Rel::IRLF:
                    newPos = Abs::IRLF;
                case Rel::IRLM:
                    newPos = Abs::IRLM;
                case Rel::IRLB:
                    newPos = Abs::IRLB;
                case Rel::IRLU:
                    newPos = Abs::IRLU;
                case Rel::IRRF:
                    newPos = Abs::IRRF;
                case Rel::IRRM:
                    newPos = Abs::IRRM;
                case Rel::IRRB:
                    newPos = Abs::IRRB;
                case Rel::IRRU:
                    newPos = Abs::IRRU;
            }
        }

    }
    Abs::DMot relToAbsDM(Rel::DMot motor){
        Abs::DMot newMot;
        if (orientation == Forwards){
            switch(motor){
                case Rel::DMR:
                    newMot = Abs::DMR;
                case Rel::DML:
                    newMot = Abs::DML;
            }

        }else{
            switch(motor){
                case Rel::DMR:
                    newMot = Abs::DML;
                case Rel::DML:
                    newMot = Abs::DMR;
            }
        }
        return newMot;
    }
    Abs::Arm relToAbsArm(Rel::Arm arm){
        Abs::Arm newArm;
        if (orientation == Forwards){
            switch(arm){
                case Rel::AR:
                    newArm = Abs::AR;
                case Rel::AL:
                    newArm = Abs::AL;
            }

        }else{
            switch(arm){
                case Rel::AR:
                    newArm = Abs::AL;
                case Rel::AL:
                    newArm = Abs::AR;
            }
        }
        return newArm;
    }
    Abs::ArmTrip relToAbsAT(Rel::ArmTrip armTrip){
        Abs::ArmTrip newAT;
        if (orientation == Forwards){
            switch(armTrip){
                case Rel::ATR:
                    newAT = Abs::ATR;
                case Rel::ATL:
                    newAT = Abs::ATL;
            }

        }else{
            switch(armTrip){
                case Rel::AR:
                    newAT = Abs::ATL;
                case Rel::AL:
                    newAT = Abs::ATR;
            }
        }

    }
    Abs::Bumper relToAbsBumper(Rel::Bumper bumper){
        Abs::Bumper newBump;
        if (orientation == Forwards){
            switch(bumper){
                case Rel::BF:
                    newBump = Abs::BF;
                case Rel::BB:
                    newBump = Abs::BB;
            }

        }else{
            switch(bumper){
                case Rel::BF:
                    newBump = Abs::BB;
                case Rel::BB:
                    newBump = Abs::BF;
            }
        }
        return newBump;
    }

    Abs::Claw relToAbsClaw(Rel::Claw claw){
        Abs::Claw newClaw;
        if (orientation == Forwards){
            switch(claw){
                case Rel::CR:
                    newClaw = Abs::CR;
                case Rel::CL:
                    newClaw = Abs::CL;
            }

        }else{
            switch(claw){
                case Rel::CR:
                    newClaw = Abs::CL;
                case Rel::CL:
                    newClaw = Abs::CR;
            }
        }
        return newClaw;

    }

    namespace Rel{
        int threshQRD(QRD position){
            Abs::QRD absPos = relToAbsQRD(position);
            return Abs::threshQRD(absPos);
        }

        int peakQRD(QRD position){
            Abs::QRD absPos = relToAbsQRD(position);
            return Abs::peakQRD(absPos);
        }

        int threshQSD(QSD position){
            Abs::QSD absPos = relToAbsQSD(position);
            return Abs::threshQSD(absPos);
        }

        int peakQSD(QSD position){
            Abs::QSD absPos = relToAbsQSD(position);
            return Abs::peakQSD(absPos);
        }

        int readQRD(QRD position, bool applyThresh){
            Abs::QRD absPos = relToAbsQRD(position);
            return Abs::readQRD(absPos,applyThresh);
        }

        int readQSD(QSD position, bool applyThresh){
            Abs::QSD absPos = relToAbsQSD(position);
            //TODO: not implemented
            return -1;
        }

        bool driveMotor(DMot motorPos, int16_t speed){
            Serial.println(motorPos);
            Abs::DMot absMot = relToAbsDM(motorPos);
            Serial.println(absMot);
            return Abs::driveMotor(absMot,speed);
        }

        bool extendArm(Arm arm, bool pos){
            Abs::Arm absArm = relToAbsArm(arm);
            return Abs::extendArm(absArm, pos);
        }

        bool openClaw(Claw claw, bool pos){
            Abs::Claw absClaw = relToAbsClaw(claw);
            return Abs::openClaw(absClaw,pos);
        }

        bool readArmTrip(ArmTrip armTrip){
            Abs::ArmTrip absAT = relToAbsAT(armTrip);
            return Abs::readArmTrip(absAT);   
        }

        bool readBumper(Bumper bumper){
            Abs::Bumper absBump = relToAbsBumper(bumper);
            return Abs::readBumper(absBump);
        }

    }
}
