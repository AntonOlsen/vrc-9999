
/*-----------------------------------------------------------------------------*/
/*  Arm control                                                                */
/*-----------------------------------------------------------------------------*/

// Global to hold requested (target) arm position
static int16_t armRequestedValue;
static int16_t armPositionLow=3800;
static int16_t armPositionMid=3000;
static int16_t armPositionHigh=2300;

/*-----------------------------------------------------------------------------*/
/*  Set requested arm position and clip to limits                              */
/*-----------------------------------------------------------------------------*/
static void SetArmPosition( int position ) {
    armRequestedValue = position;
}

/*-----------------------------------------------------------------------------*/
/*  Get requested arm position                                                 */
/*-----------------------------------------------------------------------------*/
static int GetArmPosition(void) {
    return( armRequestedValue );
}

static int16_t GetArmPot(void) {
    return( ( vexAdcGet( ArmPotR ) + vexAdcGet( ArmPotL ) ) / 2  );
}

/*-----------------------------------------------------------------------------*/
/*  arm pid (actually just P) control task                                     */
/*-----------------------------------------------------------------------------*/
task ArmPidController(void *arg) {
    (void)arg;

    int    armSensorCurrentValue;
    int    armError;
    float  armDrive;
    static float  pid_K = 0.3;

    vexTaskRegister("arm pid");

    while( TRUE ) {

        // Read the sensor value and scale
        armSensorCurrentValue = GetArmPot();
        // calculate error
        armError =  armRequestedValue - armSensorCurrentValue;
        // calculate drive
        armDrive = (pid_K * (float)armError);
        // limit drive
        if( armDrive > 127 )
            armDrive = 127;
        else
        if( armDrive < (-127) )
            armDrive = (-127);

        // send to motor
        vexMotorSet( MotorArmL, armDrive);
        vexMotorSet( MotorArmR, armDrive);

        // Don't hog cpu
        wait1Msec( 25 );
    }

    return( (msg_t) 0);
}

/*-----------------------------------------------------------------------------*/
/*  Task to control arm (and claw) movement                                    */
/*-----------------------------------------------------------------------------*/
void operatorArm(void *arg) {
    (void)arg;

    // use joystick to modify the requested position
   	// presets first, then manual up/down
    if( vexControllerGet( Btn8U ) == 1 )
        SetArmPosition( armPositionHigh );
    else
    if( vexControllerGet( Btn8R ) == 1 )
        SetArmPosition( armPositionMid );
    else
    if( vexControllerGet( Btn8D ) == 1 )
        SetArmPosition( armPositionLow );
    else
    if( vexControllerGet( Btn6U ) == 1)				// Up
        SetArmPosition( GetArmPosition() - 25 );
    else
    if( vexControllerGet( Btn6D ) == 1 )			// Down
    	// TODO - Make the motor move, regardless of position if we hold this long enough.
        SetArmPosition( GetArmPosition() + 25 );
    else
  	// Check the limit switches if no buttons are pressed
   	if ( vexDigitalPinGet( armLimitL ) == 0 || vexDigitalPinGet( armLimitL ) == 0 ) {
   		// Reset the values.
        SetArmPosition( GetArmPot() );
  		armPositionLow = GetArmPot();
   		armPositionMid = armPositionLow - 800;
   		armPositionHigh = armPositionLow - 1500;
   	}
}
