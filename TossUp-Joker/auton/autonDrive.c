
void autonDrive( int speed, int inches ) {

	float inchesL=0;
	float inchesR=0;
	int timeout=0;

	resetImeLeft();
	resetImeRight();

    // Start to motors
    vexMotorSet( MotorDriveL1, speed-2 );
    vexMotorSet( MotorDriveL2, speed-2 );
    vexMotorSet( MotorDriveR1, speed );
    vexMotorSet( MotorDriveR2, speed );

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

	// Reverse motors to stop coast
    vexMotorSet( MotorDriveL1, -speed );
    vexMotorSet( MotorDriveL2, -speed );
    vexMotorSet( MotorDriveR1, -speed );
    vexMotorSet( MotorDriveR2, -speed );

    vexSleep( 20 );

    // Stop motors
    vexMotorSet( MotorDriveL1, 0 );
    vexMotorSet( MotorDriveL2, 0 );
    vexMotorSet( MotorDriveR1, 0 );
    vexMotorSet( MotorDriveR2, 0 );

}

