/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*                        Copyright (c) James Pearman                          */
/*                                   2013                                      */
/*                            All Rights Reserved                              */
/*                                                                             */
/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*    Module:     vexuser.c                                                    */
/*    Author:     James Pearman                                                */
/*    Created:    7 May 2013                                                   */
/*                                                                             */
/*    Revisions:                                                               */
/*                V1.00  XX XXX 2013 - Initial release                         */
/*                                                                             */
/*				  V0.10  01 Jan 2014 - First version of 9999				   */
/*				  V0.11  06 Jan 2014 - Added Arm PID and Intake Control		   */
/*				  V0.11  07 Jan 2014 - Split off arm.c, intake.c, and drive.c  */
/*                                                                             */
/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*    The author is supplying this software for use with the VEX cortex        */
/*    control system. This file can be freely distributed and teams are        */
/*    authorized to freely use this program , however, it is requested that    */
/*    improvements or additions be shared with the Vex community via the vex   */
/*    forum.  Please acknowledge the work of the authors when appropriate.     */
/*    Thanks.                                                                  */
/*                                                                             */
/*    Licensed under the Apache License, Version 2.0 (the "License");          */
/*    you may not use this file except in compliance with the License.         */
/*    You may obtain a copy of the License at                                  */
/*                                                                             */
/*      http://www.apache.org/licenses/LICENSE-2.0                             */
/*                                                                             */
/*    Unless required by applicable law or agreed to in writing, software      */
/*    distributed under the License is distributed on an "AS IS" BASIS,        */
/*    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. */
/*    See the License for the specific language governing permissions and      */
/*    limitations under the License.                                           */
/*                                                                             */
/*    The author can be contacted on the vex forums as jpearman                */
/*    or electronic mail using jbpearman_at_mac_dot_com                        */
/*    Mentor for team 8888 RoboLancers, Pasadena CA.                           */
/*                                                                             */
/*-----------------------------------------------------------------------------*/

#include <stdlib.h>

#include "ch.h"  		// needs for all ChibiOS programs
#include "hal.h" 		// hardware abstraction layer header
#include "vex.h"		// vex library header
#include "smartmotor.h"
#include "vexgyro.h"
#include "robotc_glue.h"

#include "9999.h"

#include "common/gyro.c"

#include "common/arm.c"
#include "common/intake.c"
#include "common/flipper.c"
#include "drive/drive.c"
#include "auton/auton.c"

/*-----------------------------------------------------------------------------*/
/** @brief      User setup                                                     */
/*-----------------------------------------------------------------------------*/
/** @details
 *  The digital and motor ports can (should) be configured here.
 */
void vexUserSetup() {
	vexDigitalConfigure( dConfig, DIG_CONFIG_SIZE( dConfig ) );
	vexMotorConfigure( mConfig, MOT_CONFIG_SIZE( mConfig ) );
}

/*-----------------------------------------------------------------------------*/
/** @brief      User initialize                                                */
/*-----------------------------------------------------------------------------*/
/** @details
 *  This function is called after all setup is complete and communication has
 *  been established with the master processor.
 *  Start other tasks and initialize user variables here
 */
void vexUserInit() {
	// gyro_base is used by the stability control.
	gyro_base = vexAdcGet( kVexAnalog_2 );

	// vexGryo is used by the autonGyroTurn
	vexGyroInit();

    // Init the arm pot.
    SetArmPosition( GetArmPot() );

    // This task is for the sole purpose of selecting auton
    StartTask( autonSelect );

	vexDigitalPinSet( kVexDigital_9, 0 );	// Turn off Red IME LED
	vexDigitalPinSet( kVexDigital_10, 0 );	// Turn off Red Stall LED
	vexDigitalPinSet( kVexDigital_11, 0 );	// Turn off Green Auton Select LED
	vexDigitalPinSet( kVexDigital_12, 1 );	// Turn on Green Good LED


}

/*-----------------------------------------------------------------------------*/
/** @brief      Autonomous                                                     */
/*-----------------------------------------------------------------------------*/
/** @details
 *  This thread is started when the autonomous period is started
 */
msg_t vexAutonomous( void *arg ) {
    (void)arg;

    // Must call this
    vexTaskRegister("auton");

    // Start our own tasks
    StartTask( ArmPidController );

    StartTask( autonRun );

    while( TRUE ) {
    	// TODO - If disabled, kill autonRun and restart it.
        if( vexControllerCompetitonState() & kFlagDisabled ) {

        }

        // Don't hog cpu
        vexSleep( 25 );
    }

    return (msg_t)0;
}

/*-----------------------------------------------------------------------------*/
/** @brief      Driver control                                                 */
/*-----------------------------------------------------------------------------*/
/** @details
 *  This thread is started when the driver control period is started
 */
msg_t vexOperator( void *arg ) {
	(void)arg;

	int16_t		blink = 0;

	// Must call this
	vexTaskRegister("operator");

    // Start our own tasks
    StartTask( ArmPidController );

	// Run until asked to terminate
	while(!chThdShouldTerminate()) {
		// flash led/digi out
		vexDigitalPinSet( kVexDigital_12, (blink++ >> 3) & 1);	// Slow blink the enabled heartbeat (Green LED)

		operatorArm( 0 );
		operatorIntake( 0 );
		operatorFlipper( 0 );

		operatorDrive( 0 );

		// status on LCD
		vexLcdPrintf( VEX_LCD_DISPLAY_1, VEX_LCD_LINE_1, "%4.2fV   %8.1f", vexSpiGetMainBattery() / 1000.0, chTimeNow() / 1000.0 );
		vexLcdPrintf( VEX_LCD_DISPLAY_1, VEX_LCD_LINE_2, "%5.2f", getImeLeft(), getImeRight() );

		vexLcdPrintf( VEX_LCD_DISPLAY_2, VEX_LCD_LINE_1, "%4.2fV   %8.1f", vexSpiGetMainBattery() / 1000.0, chTimeNow() / 1000.0 );
		vexLcdPrintf( VEX_LCD_DISPLAY_2, VEX_LCD_LINE_2, "L %5.2f R %5.2f", getInchesLeft(), getInchesRight() );

		// Don't hog cpu
		vexSleep( 25 );
	}

	return (msg_t)0;
}
