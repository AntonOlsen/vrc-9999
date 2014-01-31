#include "gyro.h"

static int16_t gyroZero;

void resetGyro() {

	gyroZero = vexGyroGet();

}

int32_t getGyro() {

	return vexGyroGet() - gyroZero;

}
