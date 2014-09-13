/*

Joker port definitiions.

*/

// Digi IO configuration
static  vexDigiCfg  dConfig[kVexDigital_Num] = {
        { kVexDigital_1,    kVexSensorDigitalOutput, kVexConfigOutput,      0 },
        { kVexDigital_2,    kVexSensorDigitalOutput, kVexConfigOutput,      0 },
        { kVexDigital_3,    kVexSensorDigitalInput,  kVexConfigInput,       0 },
        { kVexDigital_4,    kVexSensorDigitalInput,  kVexConfigInput,       0 },
        { kVexDigital_5,    kVexSensorDigitalInput,  kVexConfigInput,       0 },
        { kVexDigital_6,    kVexSensorDigitalInput,  kVexConfigInput,       0 },
        { kVexDigital_7,    kVexSensorDigitalInput,  kVexConfigInput,       0 },
        { kVexDigital_8,    kVexSensorDigitalInput,  kVexConfigInput,       0 },
        { kVexDigital_9,    kVexSensorDigitalOutput,  kVexConfigOutput,     0 },
        { kVexDigital_10,   kVexSensorDigitalOutput,  kVexConfigOutput,     0 },
        { kVexDigital_11,   kVexSensorDigitalOutput,  kVexConfigOutput,     0 },
        { kVexDigital_12,   kVexSensorDigitalOutput,  kVexConfigOutput,     0 }
};

#define armLimitL        kVexDigital_8
#define armLimitR        kVexDigital_3

/*

Joker Motors. 9999 always starts from the center with drive wheels, arm, and intake.

Robots with power expanders will use 5/6 for drive and Y to the expander. Robots
with no expander will use 45/67 for drive. 

*/

static  vexMotorCfg mConfig[kVexMotorNum] = {
        { kVexMotor_1,      kVexMotor393T,      kVexMotorReversed,  kVexSensorNone,  0 },
        { kVexMotor_2,      kVexMotor393T,      kVexMotorReversed,  kVexSensorNone,  0 },
        { kVexMotor_3,      kVexMotor393T,      kVexMotorReversed,  kVexSensorNone,  0 },
        { kVexMotor_4,      kVexMotor393S,      kVexMotorReversed,  kVexSensorIME,   kImeChannel_1 },
        { kVexMotor_5,      kVexMotor393S,      kVexMotorReversed,  kVexSensorNone,  0 },
        { kVexMotor_6,      kVexMotor393S,      kVexMotorNormal,    kVexSensorNone,  0 },
        { kVexMotor_7,      kVexMotor393S,      kVexMotorNormal,    kVexSensorIME,   kImeChannel_2 },
        { kVexMotor_8,      kVexMotor393T,      kVexMotorNormal,    kVexSensorNone,  0 },
        { kVexMotor_9,      kVexMotor393T,      kVexMotorNormal,    kVexSensorNone,  0 },
        { kVexMotor_10,     kVexMotor393T,      kVexMotorNormal,    kVexSensorNone,  0 }
};

// Used in speedcontrol.c
int16_t driveL[3] = {  kVexMotor_7, kVexMotor_6, 0 };
int16_t driveR[3] = {  kVexMotor_4, kVexMotor_5, 0 };

#define MotorFlipperR	 kVexMotor_1

#define MotorIntakeR	 kVexMotor_2
#define MotorArmR        kVexMotor_3

#define MotorDriveR2     kVexMotor_4
#define MotorDriveR1     kVexMotor_5

#define MotorDriveL1     kVexMotor_6
#define MotorDriveL2     kVexMotor_7

#define MotorArmL 	     kVexMotor_8
#define MotorIntakeL  	 kVexMotor_9

#define MotorFlipperL  	 kVexMotor_10


#define resetImeLeft()  vexImeSetCount( kImeChannel_2, 0 )
#define resetImeRight() vexImeSetCount( kImeChannel_1, 0 )

#define getImeLeft()   vexImeMotorGetCount( kVexMotor_7 )
#define getImeRight() -vexImeMotorGetCount( kVexMotor_4 )

#define getInchesLeft()  (float) ( (float) vexImeMotorGetCount( kVexMotor_7 )/29.2)
#define getInchesRight() (float) ( (float)-vexImeMotorGetCount( kVexMotor_4 )/29.2)


#define ArmPotL          kVexAnalog_8
#define ArmPotR          kVexAnalog_3
