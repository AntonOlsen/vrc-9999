
/*-----------------------------------------------------------------------------*/
/*  Intake control                                                        */
/*-----------------------------------------------------------------------------*/

void IntakeSystemControl( short direction ) {
    long intake_l_motor;
    long intake_r_motor;

    // Limit direction to -1,0,1
    if (direction < 0) {
    	direction = -1;
    } else if (direction > 0){
    	direction = 1;
    } else {
    	direction = 0;
    }

    // Set drive
    intake_l_motor = direction * 127;
    intake_r_motor = direction * 127;

    // TODO - some magic to speed/slow alternating sides for improved intake

    // Send to motors
    vexMotorSet( MotorIntakeL, intake_l_motor );
    vexMotorSet( MotorIntakeR, intake_r_motor );
}

/*-----------------------------------------------------------------------------*/
/*  Intake Task                                                        */
/*                                                                             */
/*  Watch the joystick butons joystick Ch5, Ch7                                                     */
/*  direction is -1 (intake) or 1 (outtake)									   */
/*-----------------------------------------------------------------------------*/

task IntakeTask(void *arg) {
    short   direction;

    (void)arg;
    vexTaskRegister("Intake task");

    while( TRUE )
        {
        // Get controller
    	if( vexControllerGet( Btn5U ) == 1) {
    		direction = -1;
    	} else if( vexControllerGet( Btn5D ) == 1) {
    		direction = 1;
    	} else {
    		direction = 0;
    	}

    	IntakeSystemControl( direction );

        wait1Msec(25);
    }

    return( (msg_t) 0);
}

