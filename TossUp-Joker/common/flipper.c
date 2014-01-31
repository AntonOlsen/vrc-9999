void operatorFlipper(void *arg) {
    short   direction;

    (void)arg;

    // Get controller
 	if( vexControllerGet( Btn7U ) == 1) {
   		direction = -1;
   	} else if( vexControllerGet( Btn7D ) == 1) {
   		direction = 1;
   	} else {
   		direction = 0;
   	}

    // Send to motors
    vexMotorSet( MotorFlipperL, direction * 127 );
    vexMotorSet( MotorFlipperR, direction * 127 );

}
