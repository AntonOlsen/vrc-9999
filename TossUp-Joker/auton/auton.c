#define NOOP   0
#define TURN   1
#define DRIVE  2
#define ARM    3
#define INTAKE 4

static int16_t runAutonProgram=5;   // 0=None
static int16_t runAutonColor=1;		// 0=left, 1=right

char c0[] = "Lft";
char c1[] = "Rgt";
char *ColorName[2] = { c0, c1 };

void autonDrive( int speed, int inches );
#include "autonDrive.c"

void autonTurn( int speed, int degrees );
#include "autonTurn.c"

void autonArm( int position ) {

}

void autonIntake( int direction ) {

	IntakeSystemControl( direction );

}

#define NUM_PROGRAMS   7

char n0[] = "None";

void auton0( int side ) {
    (void) side;

	// Do nothing
	while( TRUE ) {
		vexSleep(50);
	}
}


char n1[] = "HangPushBalls";

void auton1( int side ) {

	// Pick up 2 balls
	autonIntake( -1 );
	autonDrive( 128, 18 );
	vexSleep(250);
	autonDrive( 64, 6 );
	autonDrive( 32, 6 );
	autonDrive( 32, 6 );

	// Back up to clear wall
	autonDrive( -64, 4 );
	vexSleep(100);

	// Turn 45, back toward lg balls
	autonIntake( 0 );
	autonGyroTurn(  64, -50*side );
	vexSleep(100);

	// Push ALL the balls.
	autonIntake( 0 );
	autonDrive( -128, 72 );

}

char n2[] = "HangPush1";

void auton2( int side ) {

	int topSpeed = 96;

	// Pick up 2 balls
	autonIntake( -1 );
	autonDrive( topSpeed, 18 );
	vexSleep(250);
	autonDrive( topSpeed/2, 6 );
	autonDrive( topSpeed/4, 6 );
	autonDrive( topSpeed/4, 6 );
	//autonIntake( 0 );

	// Clear wall and turn 90
	autonIntake( 0 );
	autonDrive( -topSpeed/4, 1.5 );
	autonTurn(  topSpeed/2, 90*side );
	// Square off wall
	autonDrive( -topSpeed/2, 12 );

	//armRequestedValue = armPositionMid+300;

	// Drive toward center
	autonDrive( topSpeed/2, 12 );
	vexSleep(250);

	// Turn toward first big ball
	autonTurn( topSpeed/2, 30*side );
	vexSleep(250);

	autonIntake( 0 );
	autonDrive( topSpeed/2, 12 );
	vexSleep(50);
	armRequestedValue -= 200;
	autonDrive( topSpeed/2,  6 );
	armRequestedValue -= 200;
	autonDrive( topSpeed/2,  6 );
	vexSleep(250);
	autonDrive( -topSpeed/2, 12 );
	armRequestedValue = armPositionLow;

}

char n3[] = "MidKnockStash";

void auton3( int side ) {

    SetArmPosition( GetArmPot() );
	armPositionLow = GetArmPot();
	armPositionMid = armPositionLow - 800;
	armPositionHigh = armPositionLow - 1500;
	vexSleep(100);

	armRequestedValue = armPositionMid;
	autonIntake( 0 );
	vexSleep(250);

	autonDrive(  64, 24 );
	vexSleep(200);
	autonDrive( -64, 22 );
	vexSleep(200);

	autonGyroTurn( 64, -35*side );
	vexSleep(200);

	autonDrive(  64, 34 );
	vexSleep(200);
	autonDrive( -64, 12 );
	armRequestedValue = armPositionLow;
	vexSleep(200);

	autonGyroTurn( 64, 16*side );
	vexSleep(200);

	autonDrive(  64, 36 );

	armRequestedValue = armPositionHigh;
	vexSleep(500);
	autonIntake( 1 );

	autonDrive(  64, 6 );
	autonDrive(  64, 6 );
	autonDrive(  64, 6 );
	autonIntake( 1 );
	vexSleep(1500);
	autonIntake( 0 );

}

char n4[] = "MidScoreOpp";

void auton4( int side ) {

    SetArmPosition( GetArmPot() );
	armPositionLow = GetArmPot();
	armPositionMid = armPositionLow - 800;
	armPositionHigh = armPositionLow - 1500;
	vexSleep(100);

	// Drive 36 inches
	autonDrive( 128, 30 );
	vexSleep(250);
	autonGyroTurn( 128, 40*side );
	vexSleep(100);

	// Drive 48
	autonDrive( 128, 48 );
	autonGyroTurn(128, -20*side );

	autonDrive( 128, 26 );
	vexSleep(100);

	armRequestedValue = armPositionHigh;
	vexSleep(100);
	autonGyroTurn( 128, 70*side );

	vexSleep(250);

	autonDrive(  64, 12 );
	autonIntake( 1 );
	autonDrive( 128, 6 );
	autonDrive( 128, 6 );
	autonDrive(  64, 6 );
	autonDrive(  64, 6 );
	vexSleep(1500);
	autonIntake( 0 );

	vexSleep(100);

}

char n5[] = "HangScoreBig";

void auton5( int side ) {

    SetArmPosition( GetArmPot() );
	armPositionLow = GetArmPot();
	armPositionMid = armPositionLow - 800;
	armPositionHigh = armPositionLow - 1500;
	vexSleep(100);

	autonIntake( -1 );
	// Pick up two more buckies
	autonDrive(  128, 12 );
	vexSleep(100);
	autonDrive(   64,  6 );
	vexSleep(100);
	autonDrive(   64,  6 );
	vexSleep(100);
	autonDrive(   64,  6 );
	vexSleep(100);

	// Back up
	autonDrive( -128, 18 );
	vexSleep(100);
	autonDrive(   32,  1 );

	// Flipper Down
    vexMotorSet( MotorFlipperL, 127 );
    vexMotorSet( MotorFlipperR, 127 );
	vexSleep(1000);
	vexMotorSet( MotorFlipperL, -8 );
    vexMotorSet( MotorFlipperR, -8 );
	vexSleep(25);
	vexMotorSet( MotorFlipperL, 0 );
    vexMotorSet( MotorFlipperR, 0 );

    // Turn to first big ball
	vexSleep(100);
	autonGyroTurn( 128, 75*side );

	// Back up to square off wall
	autonDrive( -64, 12 );
	autonDrive( -64, 6 );

	// Stop intake
	autonIntake( 0 );

	autonDrive( 128, 20 );

	// Flipper Up
    vexMotorSet( MotorFlipperL, -127 );
    vexMotorSet( MotorFlipperR, -127 );
	autonDrive( 128, 4 );
	vexSleep(600);

	// Hold ball
	vexMotorSet( MotorFlipperL, -16 );
    vexMotorSet( MotorFlipperR, -16 );

    // Back up a little
	autonDrive( -128, 4 );

    // Turn back toward goal
    autonGyroTurn( 128, -90*side );
	vexSleep(100);

	// Back over bump
	autonDrive(  -64, 24 );
	vexMotorSet( MotorFlipperL, 0 );
    vexMotorSet( MotorFlipperR, 0 );

	// Hold ball a little harder
	vexMotorSet( MotorFlipperL, -24 );
    vexMotorSet( MotorFlipperR, -24 );

    // Back up to barrier
    autonDrive( -128, 28 );

    // Release ball
	vexMotorSet( MotorFlipperL, 16 );
    vexMotorSet( MotorFlipperR, 16 );

    // Start backing under barrier
	autonDrive(  -127, 8 );

	// Push ball over rail
	vexMotorSet( MotorFlipperL, -32 );
    vexMotorSet( MotorFlipperR, -32 );
	autonDrive(  -127, 12 );

	// Drop flippers
	vexMotorSet( MotorFlipperL, 64 );
    vexMotorSet( MotorFlipperR, 64 );

    // Finish backing under barrier
    autonDrive(  -64, 24 );

    // Turn clear of large ball
    autonGyroTurn( 128, -90*side );

	// Raise flippers
	vexMotorSet( MotorFlipperL, -127 );
    vexMotorSet( MotorFlipperR, -127 );
	vexSleep(50);
	vexMotorSet( MotorFlipperL, -64 );
    vexMotorSet( MotorFlipperR, -64 );

    // Turn 90 more
    autonGyroTurn( 128, -90*side );
	vexMotorSet( MotorFlipperL, 0 );
    vexMotorSet( MotorFlipperR, 0 );

	// Raise arm
    armRequestedValue = armPositionHigh;
	vexSleep(250);
    autonDrive(  64, 24 );

    // Start outake
    autonDrive( 128, 6 );
    autonDrive( 128, 6 );
	autonIntake( 1 );
    autonDrive( 128, 6 );
    autonDrive( 128, 6 );
    autonDrive( 128, 6 );

	vexSleep(1500);
	autonIntake( 0 );

}

#include "skills.c"

char *ProgName[NUM_PROGRAMS] = { n0, n1, n2, n3, n4, n5, n6 };

task autonSelect( void *arg ) {
    (void)arg;

	int16_t		blink = 0;

	// We don't need this task to be persistant when competing, but it is useful for
	// testing and it gets out of the way nicely when !disabled so it doesn't hurt.
    vexTaskRegisterPersistant("autonSelect", 1);

	vexDigitalPinSet( kVexDigital_12, 0 );	// Turn off Green LED

	int ButtonLatch=0;
    vexLcdButton    Buttons;

    while( TRUE  ) {

		// Only allow changes if the competition state is disabled.
        if( vexControllerCompetitonState() & kFlagDisabled ) {

        	vexDigitalPinSet( kVexDigital_11, (blink++ >> 2) & 1);	// Fast blink the disabled heartbeat (Red LED)

    		vexLcdPrintf( VEX_LCD_DISPLAY_1, VEX_LCD_LINE_1, "Auton      %4.2fV", vexSpiGetMainBattery() / 1000.0 );
      		vexLcdPrintf( VEX_LCD_DISPLAY_2, VEX_LCD_LINE_1, "Auton      %4.2fV", vexSpiGetMainBattery() / 1000.0 );

            vexLcdPrintf( VEX_LCD_DISPLAY_1, VEX_LCD_LINE_2, "%s:%s", ColorName[runAutonColor], ProgName[runAutonProgram]);
            vexLcdPrintf( VEX_LCD_DISPLAY_2, VEX_LCD_LINE_2, "%s:%s", ColorName[runAutonColor], ProgName[runAutonProgram]);

        	// Get the buttons from both LCDs
        	Buttons = vexLcdButtonGet( VEX_LCD_DISPLAY_1 ) | vexLcdButtonGet( VEX_LCD_DISPLAY_2 ) ;

        	if( Buttons ) {

        		if( !ButtonLatch ) {
        			if( Buttons == kLcdButtonLeft ) {			// Toggle the color
        				runAutonColor = !runAutonColor;
        			} else if( Buttons == kLcdButtonCenter ) {	// Next Program
        				runAutonProgram++;
        				if (runAutonProgram >= NUM_PROGRAMS) {
        					runAutonProgram = 0;
        				}
        			} else if( Buttons == kLcdButtonRight ) {	// Reset to 0
        				runAutonProgram = 0;
        				runAutonColor = 0;
        			}
        			// Latch until the button is released (aka cheap debounce)
        			ButtonLatch = 1;
        		}
        	} else {
        		// The button was released
        		ButtonLatch = 0;
        	}
        } else {
        	vexDigitalPinSet( kVexDigital_11, 1);		// Turn off the RED LED when we can't select programs
        }
    	vexSleep(25);
    }
    return (msg_t)0;
}

task autonRun( void *arg ) {
    (void)arg;

    int side=1;

    vexTaskRegister("autonRun");

    // Init the LCD
    vexLcdPrintf( VEX_LCD_DISPLAY_1, VEX_LCD_LINE_1, "Autonomous Mode");
    vexLcdPrintf( VEX_LCD_DISPLAY_2, VEX_LCD_LINE_1, "Autonomous Mode");

    vexLcdPrintf( VEX_LCD_DISPLAY_1, VEX_LCD_LINE_2, "Run: %s:%s", ColorName[runAutonColor], ProgName[runAutonProgram]);
    vexLcdPrintf( VEX_LCD_DISPLAY_2, VEX_LCD_LINE_2, "Run: %s:%s", ColorName[runAutonColor], ProgName[runAutonProgram]);

    if( runAutonColor == 0 ) {
    	side = -1;
    }

    switch(runAutonProgram) {
	case 1:
		auton1( side );
		break;
	case 2:
		auton2( side );
		break;
	case 3:
		auton3( side );
		break;
	case 4:
		auton4( side );
		break;
	case 5:
		auton5( side );
		break;
	case 6:
		skills( side );
		break;
    case 0:
  	default:
   		auton0( side );
   		break;
    }

    return (msg_t)0;
}

