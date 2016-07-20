#pragma once

#include <stdint.h>

namespace LLRobot{
    
    namespace Abs{

        enum QRD {TFLF=0, TFRF=1, TFLB=2, TFRB=3, IDLF=4, IDRF=5, IDLB=6, IDRB=7, INR = 8,INL = 9};
        int readQRD(::LLRobot::Abs::QRD position, bool applyThresh=false);

        enum QSD {IRLF = 0,IRLM = 1,IRLB = 2,IRLU = 3,IRRF = 4,IRRM = 5,IRRB = 6, IRRU = 7};
        int readCurrentQSD(::LLRobot::Abs::QSD position, bool isControl);
        bool setCurrentQSD(::LLRobot::Abs::QSD position, bool isControl);
        
        enum DMot {DML = 0, DMR = 1};
        bool driveMotor(::LLRobot::Abs::DMot motorpos, int16_t speed);

        enum Arm {AL = 0,AR = 1};
        bool extendArm(::LLRobot::Abs::Arm arm, int16_t pos);
        
        enum Claw {CL = 0,CR = 1};
        bool openClaw(::LLRobot::Abs::Claw Claw, bool pos);

        enum ArmTrip{ATL = 0,ATR = 1};
        bool ReadArmTrip(::LLRobot::Abs::ArmTrip armTrip);
        
        enum Bumper {BF = 1,BB = 0};
        bool readBumper(::LLRobot::Abs::Bumper bumper);
    }

    namespace Rel{

        enum QRD {TFLF=0, TFRF=1, TFLB=2, TFRB=3, IDLF=4, IDRF=5, IDLB=6, IDRB=7, INR = 8,INL = 9};
        int readQRD(::LLRobot::Rel::QRD position, bool applyThresh=false);

        enum QSD {IRLF = 0,IRLM = 1,IRLB = 2,IRLU = 3,IRRF = 4,IRRM = 5,IRRB = 6, IRRU = 7};
        int readCurrentQSD(::LLRobot::Rel::QSD position, bool isControl);
        bool setCurrentQSD(::LLRobot::Rel::QSD position, bool isControl);
        
        enum DMot {DML = 0, DMR = 1};
        bool driveMotor(::LLRobot::Rel::DMot motorpos, int16_t speed);
        bool driveMotors(int16_t left, int16_t right);

        enum Claw {CL = 0,CR = 1};
        //True means open
        bool openClaw(::LLRobot::Rel::Claw Claw, bool pos);

        enum Arm {AL = 0,AR = 1};
        //True means extended
        bool extendArm(::LLRobot::Rel::Arm arm, int16_t pos);


        enum ArmTrip{ATL = 0,ATR = 1};
        bool readArmTrip(::LLRobot::Rel::ArmTrip armTrip);
        
        enum Bumper {BF = 0,BB = 1};
        bool readBumper(::LLRobot::Rel::Bumper bumper);

    }
    
    enum Orientation{FORWARDS = 0,BACKWARDS = 1};
    enum Side{LEFT = 0, RIGHT = 1};
    void setControlLock(bool state);
    void flip();
};
