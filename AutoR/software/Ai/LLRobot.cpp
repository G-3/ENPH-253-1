#include "LLRobot.h"
#include <phys253.h>

namespace LLRobot{
    //All values are absolute
    const int QRD_THRESH[] = {200,200,200,200,200,200,200,200,200,200};
    const int QRD_PEAK[] = {500,500,500,500,500,500,500,500,500,500};
    const int QSD_THRESH[] = {100,100,100,50,100,100,100,50};
    const int QSD_PEAK[] = {1024,1024,1024,1024,1024,1024,1024,1024};
    const int QSD_MICROS = 3000;

    namespace{
        // TODO: Add the pin placement for the back as well, maybe have a lookup table instead of enum


        // Analog In
        const int PIN_QSD = 0;

        const int PIN_INL = 5;
        const int PIN_INR = 6;

        enum QRDFront {pinTFLF=3,pinTFRF=2,pinIDLF=4,pinIDRF=1};
        enum QRDBack  {pinTFLB=3,pinTFRB=2,pinIDLB=4,pinIDRB=1};

        // Digital Out
        enum DOut {pinQSTReset = 4,pinMPQSD0 = 5, pinMPQSD1 = 6, pinMPQSD2 = 7, pinMPQRD=8};
        // Motor out
        enum MOut {pinDML=2, pinDMR=1};
        // Servo indicies
        enum SOut {AGL=0, AGR=1,AML=2,AMR=3};
        ServoTINAH servos[] = {RCServo0,RCServo1,RCServo2,RCServo3};
        // Digital In
        enum DIn {pinATR=8,pinATL=9,pinBF=10,pinBB=11};

        //Current orientation
        Orientation orientation = FORWARDS; 

        // Current Multiplexer States
        bool MPQRD_state = orientation;

        unsigned long timestampQSD = 0;
        bool controlLock = false;
    }   

    
    int multiplexReadQrd(Orientation direction,int pin){
        if(MPQRD_state != direction){
            digitalWrite(pinMPQRD, direction);
            MPQRD_state = direction;
        }
        int val = analogRead(pin);
        return val;
    }

    void flip(){
        switch(orientation){
            case FORWARDS:
                orientation = BACKWARDS;
                break;
            case BACKWARDS:
                orientation = FORWARDS;
                break;
        }
    }

    void setControlLock(bool value){
        controlLock = value;
    }
    
    namespace Abs{
        enum ArmValues {ExtendRight = 100, ExtendLeft = 100, RetractRight = 30, RetractLeft = 30};
        enum ClawValues {OpenRight = 100, OpenLeft = 100, CloseRight = 30, CloseLeft = 30};

        int readCurrentQSD(bool isControl){
            //Allow control when control lock is on
            //Allow everthing else when everything else is on
            if (isControl == controlLock){
                if ((micros() - timestampQSD) > QSD_MICROS){
                        return analogRead(PIN_QSD);
                }
            }
            return -1;
        }

        bool setCurrentQSD(QSD position, bool isControl){
            if (isControl == controlLock){
                if ((micros() - timestampQSD) > QSD_MICROS){
                    digitalWrite(pinMPQSD0, position % 1);
                    digitalWrite(pinMPQSD1, position % 2);
                    digitalWrite(pinMPQSD2, position % 4);
                    timestampQSD = micros();
                    return true;   
                }
            }
            return false;
        }
        

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
                    val = multiplexReadQrd(FORWARDS,pinTFLF);
                    break;

                case TFRF:
                    val = multiplexReadQrd(FORWARDS,pinTFRF);
                    break;

                case TFLB:
                    val = multiplexReadQrd(BACKWARDS,pinTFLB);
                    break;

                case TFRB:
                    val = multiplexReadQrd(BACKWARDS,pinTFRB);
                    break;

                case IDLF:
                    val = multiplexReadQrd(FORWARDS,pinIDLF);
                    break;

                case IDRF:
                    val = multiplexReadQrd(FORWARDS,pinIDRF);
                    break;

                case IDLB:
                    val = multiplexReadQrd(BACKWARDS,pinIDLB);
                    break;

                case IDRB:
                    val = multiplexReadQrd(BACKWARDS,pinIDRB);
                    break;
                case INL:
                    val = analogRead(PIN_INL);
                    break;
                case INR:
                    val = analogRead(PIN_INR);
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
                    motor.speed(pinDML, speed);
                    return true;
                case DMR:
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
                        break;
                    case AL:
                        servos[AML].write(ExtendLeft);
                        break;
                }
            }
            else{
                switch(arm){
                    case AR:
                        servos[AMR].write(RetractRight);
                        break;
                    case AL:
                        servos[AML].write(RetractLeft);
                        break;
                }
            }

            return true;
        }

        bool openClaw(Claw claw, bool pos){
            if (pos){
                switch(claw){
                    case CR:
                        servos[CR].write(OpenRight);
                        break;
                    case CL:
                        servos[CL].write(OpenLeft);
                        break;
                }
            }
            else{
                switch(claw){
                    case CR:
                        servos[AMR].write(CloseRight);
                        break;
                    case CL:
                        servos[AMR].write(CloseLeft);
                        break;
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
        if (orientation == FORWARDS){
            switch(position){
                case Rel::TFLF:
                    newPos = Abs::TFLF;
                    break;
                case Rel::TFRF:
                    newPos = Abs::TFRF;
                    break;
                case Rel::TFLB:
                    newPos = Abs::TFLB;
                    break;
                case Rel::TFRB:
                    newPos = Abs::TFRB;
                    break;
                case Rel::IDLF:
                    newPos = Abs::IDLF;
                    break;
                case Rel::IDRF:
                    newPos = Abs::IDRF;
                    break;
                case Rel::IDLB:
                    newPos = Abs::IDLB;
                    break;
                case Rel::IDRB:
                    newPos = Abs::IDRB;
                    break;
                case Rel::INL:
                    newPos = Abs::INL;
                    break;
                case Rel::INR:
                    newPos = Abs::INR;
                    break;
            }
        }
        else{
            switch(position){
                case Rel::TFLF:
                    newPos = Abs::TFRB;
                    break;
                case Rel::TFRF:
                    newPos = Abs::TFLB;
                    break;
                case Rel::TFLB:
                    newPos = Abs::TFRF;
                    break;
                case Rel::TFRB:
                    newPos = Abs::TFLF;
                    break;
                case Rel::IDLF:
                    newPos = Abs::IDRB;
                    break;
                case Rel::IDRF:
                    newPos = Abs::IDLB;
                    break;
                case Rel::IDLB:
                    newPos = Abs::IDRF;
                    break;
                case Rel::IDRB:
                    newPos = Abs::IDLF;
                    break;
                case Rel::INL:
                    newPos = Abs::INR;
                    break;
                case Rel::INR:
                    newPos = Abs::INL;
                    break;
            }
        }
        return newPos;

    }
    Abs::QSD relToAbsQSD(Rel::QSD position){
        Abs::QSD newPos;
        if (orientation == FORWARDS){
            switch(position){
                case Rel::IRLF:
                    newPos = Abs::IRLF;
                    break;
                case Rel::IRLM:
                    newPos = Abs::IRLM;
                    break;
                case Rel::IRLB:
                    newPos = Abs::IRLB;
                    break;
                case Rel::IRLU:
                    newPos = Abs::IRLU;
                    break;
                case Rel::IRRF:
                    newPos = Abs::IRRF;
                    break;
                case Rel::IRRM:
                    newPos = Abs::IRRM;
                    break;
                case Rel::IRRB:
                    newPos = Abs::IRRB;
                    break;
                case Rel::IRRU:
                    newPos = Abs::IRRU;
                    break;
            }
        }
        else{
            switch(position){
                case Rel::IRLF:
                    newPos = Abs::IRLF;
                    break;
                case Rel::IRLM:
                    newPos = Abs::IRLM;
                    break;
                case Rel::IRLB:
                    newPos = Abs::IRLB;
                    break;
                case Rel::IRLU:
                    newPos = Abs::IRLU;
                    break;
                case Rel::IRRF:
                    newPos = Abs::IRRF;
                    break;
                case Rel::IRRM:
                    newPos = Abs::IRRM;
                    break;
                case Rel::IRRB:
                    newPos = Abs::IRRB;
                    break;
                case Rel::IRRU:
                    newPos = Abs::IRRU;
                    break;
            }
        }

    }
    Abs::DMot relToAbsDM(Rel::DMot motor){
        Abs::DMot newMot;
        if (orientation == FORWARDS){
            switch(motor){
                case Rel::DMR:
                    newMot = Abs::DMR;
                    break;
                case Rel::DML:
                    newMot = Abs::DML;
                    break;
            }

        }else{
            switch(motor){
                case Rel::DMR:
                    newMot = Abs::DML;
                    break;
                case Rel::DML:
                    newMot = Abs::DMR;
                    break;
            }
        }
        return newMot;
    }
    Abs::Arm relToAbsArm(Rel::Arm arm){
        Abs::Arm newArm;
        if (orientation == FORWARDS){
            switch(arm){
                case Rel::AR:
                    newArm = Abs::AR;
                    break;
                case Rel::AL:
                    newArm = Abs::AL;
                    break;
            }

        }else{
            switch(arm){
                case Rel::AR:
                    newArm = Abs::AL;
                    break;
                case Rel::AL:
                    newArm = Abs::AR;
                    break;
            }
        }
        return newArm;
    }
    Abs::ArmTrip relToAbsAT(Rel::ArmTrip armTrip){
        Abs::ArmTrip newAT;
        if (orientation == FORWARDS){
            switch(armTrip){
                case Rel::ATR:
                    newAT = Abs::ATR;
                    break;
                case Rel::ATL:
                    newAT = Abs::ATL;
                    break;
            }

        }else{
            switch(armTrip){
                case Rel::AR:
                    newAT = Abs::ATL;
                    break;
                case Rel::AL:
                    newAT = Abs::ATR;
                    break;
            }
        }

    }
    Abs::Bumper relToAbsBumper(Rel::Bumper bumper){
        Abs::Bumper newBump;
        if (orientation == FORWARDS){
            switch(bumper){
                case Rel::BF:
                    newBump = Abs::BF;
                    break;
                case Rel::BB:
                    newBump = Abs::BB;
                    break;
            }

        }else{
            switch(bumper){
                case Rel::BF:
                    newBump = Abs::BB;
                    break;
                case Rel::BB:
                    newBump = Abs::BF;
                    break;
            }
        }
        return newBump;
    }

    Abs::Claw relToAbsClaw(Rel::Claw claw){
        Abs::Claw newClaw;
        if (orientation == FORWARDS){
            switch(claw){
                case Rel::CR:
                    newClaw = Abs::CR;
                    break;
                case Rel::CL:
                    newClaw = Abs::CL;
                    break;
            }

        }else{
            switch(claw){
                case Rel::CR:
                    newClaw = Abs::CL;
                    break;
                case Rel::CL:
                    newClaw = Abs::CR;
                    break;
            }
        }
        return newClaw;

    }

    namespace Rel{

        int readCurrentQSD(bool isControl){
            return Abs::readCurrentQSD(isControl);
        }
        bool setCurrentQSD(QSD position, bool isControl){
            Abs::QSD absPos = relToAbsQSD(position);
            return Abs::readCurrentQSD(absPos,isControl);
        }

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
            Abs::DMot absMot = relToAbsDM(motorPos);
            return Abs::driveMotor(absMot,speed);
        }

        bool driveMotors(int16_t left, int16_t right){
            return driveMotor(DML, left) & driveMotor(DMR, right);
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
