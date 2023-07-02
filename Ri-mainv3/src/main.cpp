#include "mbed.h"
#include "modeRun.h"

void setup() {
    swDrible.mode(PullUp);
    swKicker.mode(PullUp);
    // dribler.write(0);
    dribbler.turnOff();
    pc.baud(2000000);
    imu.init();
    MD.setVelocityZero();
    initModeRun();
    imu.setZero();
    timer.start();
    pidDt.start();
    tickCalcIMU.attach_us(&attitudeControl, 10000);
    setPIDGain();
    timeFromLastImuReset.start();
}

int main(void) {
    setup();
    while (1) {
        modeRun();
    }
}