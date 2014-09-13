// PID Speed Control - Feedback loop for speed and direction control.
// error		- The difference between what we want and what we have.
// Proportional - Proportional to the error
//                How far are we from our desired speed?
// Integral     - Error over time
//                How long has the error existed?
// Derivative   - Rate of change of the error
//                How fast are we approaching the desired speed?

// Since actual calculus is difficult within the scope of this program we will
// use simpler approximations of the more complex equations.

// Gain values for speed.
static float speedKp = 1;		// Proportional gain
static float speedKi = 0.01;	// Integral gain
static float speedKd = 0.01;	// Derivative gain

// Gain for differential speed.
static float diffKp = 1;		// Proportional gain
static float diffKi = 0.01;		// Integral gain
static float diffKd = 0.01;		// Derivative gain

// The gain variables could be local inside speedControl, but we can keep them
// in global so we can tune the values with the LCD.

// Arrays to track the last x errors for calculating I and D.
//static int16_t num_error = 5;
//static int16_t speed_err[5];	// Difference between desired drive speed and actual
//static int16_t diff_err[5];		// Difference between relative left and right drive speed

// PID Speed Control for Robot
// speed = 0 to 100 for stop to full speed. Negative for reverse.
// turn  = 0 to 100 for straight to spin right. Negative for left spin.

// Drive motors are stored in global arrays, driveL[3] and driveR[3]
// these are defined in 9999.h

void speedControl( int16_t speed, int16_t turn ) {

	int16_t speedL;
	int16_t speedR;

	int16_t targetL;
	int16_t targetR;

	int16_t errorL;
	int16_t errorR;
	int16_t errorD;

	// Determine velocities. Returned in ticks per second.
    speedL = getVelocity( driveL[0] );
    speedR = getVelocity( driveR[0] );

    // Determine the desired motor velocities. Convert to ticks per second.
    // target is max_speed * speed / 100
    targetL = speed;
    targetR = speed;

    // Turning states
    //	100		L =  speed		R = -speed
    //   50		L =  speed      R =  speed * .5
    //    0		L =  speed		R =  speed
    //  -50     L = -speed *.5  R =  speed
    // -100		L = -speed		R =  speed

    if ( turn < 0 ) {
    	targetL -= speed * -turn / 100;
    } else if ( turn > 0 ) {
    	targetR -= speed * turn / 100;
    }

    // Determine the 3 errors: left, right, and differential




}


// Global to store drive IME counts
static int16_t driveLastCount[10];
static float driveLastMillis[10];

// Return the velocity of the motor.
int16_t getVelocity( int16_t motor ) {
	int16_t velocity;
	float seconds;

	seconds = (millis()/1000) - driveCountTime[motor];
	driveCountTime[motor] = seconds;

	if (!seconds) {
		return 0;
	}

	// Set velocity to counts/second
	velocity = (float) vexImeMotorGetCount( motor ) / seconds;

	return velocity;
}



