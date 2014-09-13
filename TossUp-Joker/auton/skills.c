char n6[] = "Skills";

void skills( int side ) {

	int topSpeed = 96+16;

    SetArmPosition( GetArmPot() );
	armPositionLow = GetArmPot();
	armPositionMid = armPositionLow - 800;
	armPositionHigh = armPositionLow - 1500;
	vexSleep(100);

	// Blue Hang Zone
	// Pick up 2 balls
	autonIntake( -1 );
	autonDrive( topSpeed/2, 18 );	// Drive to 2 balls
	vexSleep(100);
	autonDrive( topSpeed/2, 6 );	// Drive again
	vexSleep(100);
	autonDrive( topSpeed/4, 6 );	// Bump
	vexSleep(50);
	autonDrive( topSpeed/4, 6 );	// Bump
	autonDrive( topSpeed/4, 6 );	// Bump

	autonDrive(  -topSpeed/4, 2 );	// Back away from wall 2 inches
	autonGyroTurn( topSpeed/4, -1);	// Turn to avoid mid zone preload

    armRequestedValue = armPositionMid;

	// Back up over bump
	autonDrive( -topSpeed/2, 28 );

	// Blue Middle zone
	autonDrive(  -topSpeed/2, 24 );
	autonIntake( 0 );
	autonGyroTurn( topSpeed/4, 2);	// Turn to undo avoid mid zone preload

	// Knock 1 ball
    armRequestedValue = armPositionHigh;
	autonDrive( -topSpeed/2, 24 );
    armRequestedValue = armPositionLow;
    vexSleep(250);

	// Drive forward
	autonDrive( topSpeed/2, 9);			// Drive away from barrier
	autonIntake( -1 );
	autonGyroTurn( topSpeed/2, 90);		// Turn to center
	autonDrive( -topSpeed/2, 12 );		// Square off wall

	autonDrive( topSpeed/2, 20);			// Drive to tape
	autonGyroTurn( topSpeed/2, 90);			// Turn to stash

	// Blue Goal Zone
	autonDrive( topSpeed/2, 38);			// Drive toward stash
    armRequestedValue = armPositionHigh;
    vexSleep(250);
	autonIntake( 0 );		// Outtake

    // bump bump
	autonDrive( topSpeed/2, 18 );
	vexSleep(100);
	autonDrive( topSpeed/2, 6 );
	vexSleep(100);
	autonDrive( topSpeed/2, 6 );
	autonDrive( topSpeed/2, 6 );
	autonDrive( topSpeed/2, 6 );
	vexSleep(100);
	autonIntake( 1 );		// Outtake
	autonDrive( topSpeed/4, 6 );
	vexSleep(100);
	autonDrive( topSpeed/4, 6 );
	vexSleep(1600);
	autonIntake( 0 );

	// Back up to clear blue goal
	autonDrive( -topSpeed/2, 16 );
    armRequestedValue = armPositionLow;
	autonGyroTurn( topSpeed/2, -88);
	autonDrive( topSpeed/2, 2*24 );  		// Drive across field
	autonGyroTurn( topSpeed/2, -2);
	autonDrive( topSpeed/2, 2*24 +6 );		// Drive across field

	// Red Goal Zone
	autonDrive( -topSpeed/4, 3 );
	autonGyroTurn( topSpeed, -100);
	autonDrive( -topSpeed/2, 18 );			// Square off wall
	autonDrive( -topSpeed/2, 6 );			// Square off wall
	autonDrive( -topSpeed/2, 6 );			// Square off wall

	autonDrive( topSpeed/2, 2*24);
	autonIntake( -1 );		// Intake
	autonDrive( topSpeed/2, 24);
	vexSleep(250);
    armRequestedValue = armPositionMid;

    // Red Mid Zone
	autonDrive( topSpeed/2, 24);		// Over bump

	// Red Hang Zone
	armRequestedValue = armPositionLow;
	vexSleep(1000);

	autonDrive( topSpeed/2, 6);		// Pick up 2
	vexSleep(100);
	autonDrive( topSpeed/2, 6);		// bump
	vexSleep(100);
	autonDrive( topSpeed/2, 6);		// bump
	vexSleep(100);
	autonDrive( 64, 6);		// bump
	vexSleep(50);

	autonDrive(  -topSpeed/4, 2 );	// Back away from wall 2 inches
	autonGyroTurn( topSpeed/2, 1);	// Turn to avoid mid zone preload

    armRequestedValue = armPositionMid;

	// Back up over bump
	autonDrive( -topSpeed/2, 28 );

	// Red Mid Zone
	autonIntake( 0 );
	autonDrive(  -topSpeed/2, 24 );
	autonGyroTurn( topSpeed/4, -2);	// Turn to undo avoid mid zone preload

	// Knock 1 ball
    armRequestedValue = armPositionHigh;
	autonDrive( -topSpeed/2, 24 );
    armRequestedValue = armPositionLow;
    vexSleep(250);

	// Drive forward
	autonDrive( topSpeed/2, 9);			// Drive away from barrier
	autonGyroTurn( topSpeed/2, -90);		// Turn to center
	autonDrive( -topSpeed/2, 12 );		// Square off wall

	autonDrive( topSpeed/2, 18);			// Drive to tape
	autonGyroTurn( topSpeed, -100);			// Turn to stash
	autonDrive( topSpeed/2, 40);			// Drive toward stash
    armRequestedValue = armPositionHigh;
    vexSleep(250);

    // bump bump
	autonDrive( topSpeed/2, 18 );
	vexSleep(100);
	autonDrive( topSpeed/2, 6 );
	vexSleep(100);
	autonDrive( topSpeed/2, 6 );
	vexSleep(100);
	autonIntake( 1 );		// Outtake
	autonDrive( topSpeed/4, 6 );
	vexSleep(100);
	autonDrive( topSpeed/4, 6 );
	vexSleep(1600);
	autonIntake( 0 );

	autonIntake( 0 );

}
