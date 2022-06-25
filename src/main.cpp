#include "mbed.h"
#include "modeRun.h"

void setup() {
    swDrible.mode(PullUp);
    swKicker.mode(PullUp);
    pc.baud(2000000);
    imu.init();
    MD.setVelocityZero();
    initModeRun();
    imu.setZero();
    timer.start();
    pidDt.start();
    tickCalcIMU.attach_us(&attitudeControl,6000);
}

int main(void) {
    setup();
    while (1) {
        modeRun();
    }
}