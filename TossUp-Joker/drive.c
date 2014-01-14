static int16_t gyro_base;
static int16_t gyro_err[5];

/*-----------------------------------------------------------------------------*/
/*  Drive control task                                                         */
/*                                                                             */
/*  Uses joystick Ch3, Ch1                                                     */
/*-----------------------------------------------------------------------------*/
void DriveSystemArcadeDrive( short forward, short turn ) {
    long drive_l_motor;
    long drive_r_motor;
    int i;
    float pG = 0.2;

    int16_t gyro_raw;
    int16_t gyro_error;

    // Set drive
    drive_l_motor = forward + turn;
    drive_r_motor = forward - turn;

    // normalize drive so max is 127 if any drive is over 127
    int max = abs(drive_l_motor);
    if (abs(drive_r_motor)  > max)
        max = abs(drive_r_motor);
    if (max>127) {
        drive_l_motor = 127 * drive_l_motor / max;
        drive_r_motor = 127 * drive_r_motor  / max;
    }

    gyro_raw = vexAdcGet( kVexAnalog_1 );

    gyro_error = (gyro_base - gyro_raw);
    for( i=0;i<4;i++) {
    	gyro_error += gyro_err[i];
        gyro_err[i+1] = gyro_err[i];
    }
    gyro_err[0] = (gyro_base - gyro_raw);

//	vexLcdPrintf( VEX_LCD_DISPLAY_1, VEX_LCD_LINE_1, "%4d %4d", gyro_base, gyro_error );
    if ( GetArmPosition() < (armPositionMid-50) && gyro_error < 0) {
    	drive_l_motor += ( gyro_error * pG );
    	drive_r_motor += ( gyro_error * pG );
    }

    // Send to motors
    // left drive
    vexMotorSet( MotorDriveL1, drive_l_motor );
    vexMotorSet( MotorDriveL2, drive_l_motor );

    // right drive
    vexMotorSet( MotorDriveR1, drive_r_motor );
    vexMotorSet( MotorDriveR2, drive_r_motor );
}

/*-----------------------------------------------------------------------------*/
/*  Drive control task                                                         */
/*-----------------------------------------------------------------------------*/

task DriveTask(void *arg) {
    short   forward, turn;

    (void)arg;
    vexTaskRegister("Drive task");

    while( TRUE ) {

    	// Get controller
        if( abs( vexControllerGet( Ch3 ) ) > 10 )
            forward = vexControllerGet( Ch3 );
        else
            forward = 0;

        if( abs( vexControllerGet( Ch1 ) ) > 10 )
            turn = vexControllerGet( Ch1 );
        else
            turn = 0;

        if( abs(turn) < 80) {
        	turn *= 0.50;
        } else if( abs(turn) < 100 ) {
        	turn *= 0.75;
        }

        DriveSystemArcadeDrive( forward, turn );

        wait1Msec(25);
    }

    return( (msg_t) 0);
}

