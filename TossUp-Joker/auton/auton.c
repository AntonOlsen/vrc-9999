#define NOOP   0
#define TURN   1
#define DRIVE  2
#define ARM    3
#define INTAKE 4

static int16_t runAutonProgram=0;   // 0=None
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

#define NUM_PROGRAMS   4

char n0[] = "None";

void auton0( int side ) {
    (void) side;

	// Do nothing
	while( TRUE ) {
		vexSleep(50);
	}
}


char n1[] = "Hang1";

void auton1( int side ) {

	// Pick up 2 balls
	autonIntake( -1 );
	autonDrive( 128, 18 );
	vexSleep(250);
	autonDrive( 64, 6 );
	autonDrive( 32, 6 );
	autonDrive( 32, 6 );
	//autonIntake( 0 );

	// Clear wall and turn 90
	autonIntake( 0 );
	autonDrive( -64, 1.5 );
	autonTurn(  48, 90*side );
	// Square off wall
	autonDrive( -64, 12 );

	//armRequestedValue = armPositionMid+300;

	// Drive toward center
	autonDrive( 128, 12 );
	vexSleep(250);

	// Turn toward first big ball
	autonTurn( 64, 30*side );
	vexSleep(250);

	autonIntake( 0 );
	autonDrive( 64, 12 );
	vexSleep(50);
	armRequestedValue -= 200;
	autonDrive( 48,  6 );
	armRequestedValue -= 200;
	autonDrive( 48,  6 );
	vexSleep(250);
	autonDrive( -64, 12 );
	armRequestedValue = armPositionLow;

	// Turn and square off wall.
	autonTurn( 64, 40*side );
	vexSleep(250);
	autonDrive( -64, 12 );
	vexSleep(100);
	autonDrive( -128, 6 );
	vexSleep(100);

	armRequestedValue = armPositionMid+300;
	autonDrive( 96, 54 );
	armRequestedValue = armPositionLow;
	vexSleep(100);
	//autonTurn( 64, -5*side );
	autonDrive( 128, 48 );
	vexSleep(100);
	armRequestedValue = armPositionMid;
	autonTurn(  64, -5*side );
	autonDrive( 128, 24 );
	vexSleep(100);
	armRequestedValue = armPositionHigh;
	autonDrive( 32, 24 );
	autonDrive( 32, 6 );
	autonDrive( 32, 6 );
	autonDrive( 32, 6 );

	autonIntake( 1 );

}

char n2[] = "Hang2";

void auton2( int side ) {

	// Pick up 2 balls
	autonIntake( -1 );
	autonDrive( 128, 18 );
	vexSleep(250);
	autonDrive( 64, 6 );
	autonDrive( 32, 6 );
	autonDrive( 32, 6 );
	//autonIntake( 0 );

	// Clear wall and turn 90
	autonIntake( 0 );
	autonDrive( -64, 1.5 );
	autonTurn(  48, 90*side );
	// Square off wall
	autonDrive( -64, 12 );

	//armRequestedValue = armPositionMid+300;

	// Drive toward center
	autonDrive( 128, 12 );
	vexSleep(250);

	// Turn toward first big ball
	autonTurn( 64, 30*side );
	vexSleep(250);

	autonIntake( 0 );
	autonDrive( 64, 12 );
	vexSleep(50);
	armRequestedValue -= 200;
	autonDrive( 48,  6 );
	armRequestedValue -= 200;
	autonDrive( 48,  6 );
	vexSleep(250);
	autonDrive( -64, 12 );
	armRequestedValue = armPositionLow;

}


char n3[] = "Mid1";

void auton3( int side ) {

    SetArmPosition( GetArmPot() );
	armPositionLow = GetArmPot();
	armPositionMid = armPositionLow - 800;
	armPositionHigh = armPositionLow - 1500;
	vexSleep(100);

	armRequestedValue = armPositionMid;
	autonIntake( 0 );
	vexSleep(500);

	autonDrive(  64, 24 );
	vexSleep(200);
	autonDrive( -64, 24 );
	vexSleep(200);

	autonTurn( 64, -30*side );
	vexSleep(200);

	autonDrive(  64, 36 );
	vexSleep(200);
	autonDrive( -64, 12 );
	armRequestedValue = armPositionLow;
	vexSleep(200);

	autonTurn( 64, 35*side );
	vexSleep(200);

	autonDrive(  64, 24 );
	autonIntake( 1 );

	vexSleep(100);

}

char *ProgName[NUM_PROGRAMS] = { n0, n1, n2, n3 };

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
//    		vexLcdPrintf( VEX_LCD_DISPLAY_2, VEX_LCD_LINE_1, "Auton      %4.2fV", vexSpiGetMainBattery() / 1000.0 );

            vexLcdPrintf( VEX_LCD_DISPLAY_1, VEX_LCD_LINE_2, "%s:%s", ColorName[runAutonColor], ProgName[runAutonProgram]);
//          vexLcdPrintf( VEX_LCD_DISPLAY_2, VEX_LCD_LINE_2, "%s:%s", ColorName[runAutonColor], ProgName[runAutonProgram]);

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

    int16_t blink=0;
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
    	case 0:
  	default:
   		auton0( side );
   		break;
    }

    return (msg_t)0;
}

