


void autonGyroTurn( int speed, int degrees ) {

	float inchesL=0;
	float inchesR=0;

	int timeout=0;
	int turned=0;
	int error=0;

	int gyroGain=1;

	// Reverse speed if turning left (negative degrees)
	if (degrees < 0) {
		speed = -speed;
	}

	// Gyro returns 10x the actual degrees.
	// We set direction above, so we can deal with positive angles from here on
	degrees = abs(degrees) * (10 - 1); // Lose 10% of the angle.

	// Used for stall detection
	resetImeLeft();
	resetImeRight();

	// Start turn
    vexMotorSet( MotorDriveL1, speed );
    vexMotorSet( MotorDriveL2, speed );
    vexMotorSet( MotorDriveR1, -speed );
    vexMotorSet( MotorDriveR2, -speed );

	// Call our gyro reset function
	resetGyro();

    while( TRUE ) {

		// getGyro returns degrees turned since last resetGyro()
		turned = abs(getGyro());
		error = degrees - turned;

		// Simple PID which is really just P with a gain of 1.
		speed = speed * error / degrees;

		if (speed < 0) {
			if (speed > -32) {
				speed = -32;
			}
		} else {
			if (speed < 32) {
				speed = 32;
			}
		}

		vexLcdPrintf( VEX_LCD_DISPLAY_1, VEX_LCD_LINE_2, "G %4d, %4d", getGyro(), speed );
		vexLcdPrintf( VEX_LCD_DISPLAY_2, VEX_LCD_LINE_2, "G %4d, %4d", getGyro(), speed );

		// Stall detection still uses IMEs
		if (inchesL == getInchesLeft() && inchesR == getInchesRight() ) {
			timeout++;
			if( timeout > 45 ) {
				vexDigitalPinSet( kVexDigital_10, 1 );	// Turn on Red Stall LED
				vexLcdPrintf( VEX_LCD_DISPLAY_1, VEX_LCD_LINE_2, "Stall %4d", getGyro() );
				vexLcdPrintf( VEX_LCD_DISPLAY_2, VEX_LCD_LINE_2, "Stall %4d", getGyro() );
				break;
			}
		}

		inchesL = getInchesLeft();
		inchesR = getInchesRight();

		if ( abs(turned) > degrees ) {
			vexLcdPrintf( VEX_LCD_DISPLAY_1, VEX_LCD_LINE_2, "Break %4d", getGyro() );
			vexLcdPrintf( VEX_LCD_DISPLAY_2, VEX_LCD_LINE_2, "Break %4d", getGyro() );
			break;
		}

		vexMotorSet( MotorDriveL1, speed );
		vexMotorSet( MotorDriveL2, speed );
		vexMotorSet( MotorDriveR1, -speed );
		vexMotorSet( MotorDriveR2, -speed );

		vexSleep(10);
	}

	// Reverse the motors a moment to halt momentum
	vexMotorSet( MotorDriveL1, -speed );
	vexMotorSet( MotorDriveL2, -speed );
	vexMotorSet( MotorDriveR1, speed );
	vexMotorSet( MotorDriveR2, speed );

	vexSleep(20);

    // Stop motors
    vexMotorSet( MotorDriveL1, 0 );
    vexMotorSet( MotorDriveL2, 0 );
    vexMotorSet( MotorDriveR1, 0 );
    vexMotorSet( MotorDriveR2, 0 );

}


void autonTurn( int speed, int degrees ) {

	float inches;
	float inchesL=0;
	float inchesR=0;
	int timeout=0;

	inches = ( ((float)abs(degrees)/(float)360) * (float)44 );

	if (degrees < 0) {
		speed = -speed;
	}

    vexLcdPrintf( VEX_LCD_DISPLAY_2, VEX_LCD_LINE_1, "Turn %f:%d", inches, speed);

	resetImeLeft();
	resetImeRight();

	// Start turn
    vexMotorSet( MotorDriveL1, speed );
    vexMotorSet( MotorDriveL2, speed );
    vexMotorSet( MotorDriveR1, -speed );
    vexMotorSet( MotorDriveR2, -speed );

	while( TRUE ) {
		vexLcdPrintf( VEX_LCD_DISPLAY_1, VEX_LCD_LINE_2, "L %5.2f R %5.2f", getInchesLeft(), getInchesRight() );
		vexLcdPrintf( VEX_LCD_DISPLAY_2, VEX_LCD_LINE_2, "L %5.2f R %5.2f", getInchesLeft(), getInchesRight() );

		if (inchesL == getInchesLeft() && inchesR == getInchesRight() ) {
			timeout++;
			if( timeout > 30 ) {
				break;
			}
		}
		inchesL = getInchesLeft();
		inchesR = getInchesRight();

		if( abs(inchesL) > inches || abs(inchesR) > inches ) {
			break;
		}
		vexSleep(5);
	}

    // Reverse motors for a moment to stop coast
    vexMotorSet( MotorDriveL1, -speed/2 );
    vexMotorSet( MotorDriveL2, -speed/2 );
    vexMotorSet( MotorDriveR1,  speed/2 );
    vexMotorSet( MotorDriveR2,  speed/2 );

    vexSleep( abs(speed/8) );

    // Stop motors
    vexMotorSet( MotorDriveL1, 0 );
    vexMotorSet( MotorDriveL2, 0 );
    vexMotorSet( MotorDriveR1, 0 );
    vexMotorSet( MotorDriveR2, 0 );

}

