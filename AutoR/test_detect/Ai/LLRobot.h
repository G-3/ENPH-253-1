#pragma once

#include <stdint.h>

namespace LLRobot{


    namespace Abs{
        enum QRD {TFLF=0, TFRF=1, TFLB=2, TFRB=3, IDLF=4, IDRF=5, IDLB=6, IDRB=7, IAR = 8,IAB = 9};
        int readQRD(::LLRobot::Abs::QRD position, bool applyThresh=false);

        enum QSD {IRLF = 0,IRLM = 1,IRLB = 2,IRLU = 3,IRRF = 4,IRRM = 5,IRRB = 6, IRRU = 7};
        int readQSD(::LLRobot::Abs::QSD position, bool applyThresh=false);
        
        enum DMot {DML = 0, DMR = 1};
        bool driveMotor(::LLRobot::Abs::DMot motorpos, int16_t speed);

        enum Arm {AL = 0,AR = 1};
        bool extendArm(::LLRobot::Abs::Arm arm, int16_t pos);
        
        enum Claw {CL = 0,CR = 1};
        bool openClaw(::LLRobot::Abs::Claw Claw, int16_t pos);

        enum ArmTrip{ATL = 0,ATR = 1};
        bool ReadArmTrip(::LLRobot::Abs::ArmTrip armTrip);
        
        enum Bumper {BF = 1,BB = 0};
        bool readBumper(::LLRobot::Abs::Bumper bumper);
    }

    namespace Rel{
        enum QRD {TFLF=0, TFRF=1, TFLB=2, TFRB=3, IDLF=4, IDRF=5, IDLB=6, IDRB=7, INR = 8,INB = 9};
        int readQRD(::LLRobot::Rel::QRD position, bool applyThresh=false);

        enum QSD {IRLF = 0,IRLM = 1,IRLB = 2,IRLU = 3,IRRF = 4,IRRM = 5,IRRB = 6, IRRU = 7};
        int readQSD(::LLRobot::Rel::QSD position, bool applyThresh=false);
        
        enum DMot {DML = 0, DMR = 1};
        bool driveMotor(::LLRobot::Rel::DMot motorpos, int16_t speed);
        bool driveMotors(int16_t left, int16_t right);

        enum Claw {CL = 0,CR = 1};
        bool openClaw(::LLRobot::Rel::Claw Claw, int16_t pos);

        enum Arm {AL = 0,AR = 1};
        bool extendArm(::LLRobot::Rel::Arm arm, bool pos);

        enum ArmTrip{ATL = 0,ATR = 1};
        bool ReadArmTrip(::LLRobot::Rel::ArmTrip armTrip);
        
        enum Bumper {BF = 0,BB = 1};
        bool readBumper(::LLRobot::Rel::Bumper bumper);
    }
    enum Orientation{Forwards = 0,Backwards = 1};
};
