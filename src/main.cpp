#include "mbed.h"
#include "modeRun.h"
// Timer timer;
void setup() {
    swDrible.mode(PullUp);
    swKicker.mode(PullUp);
    pc.baud(2000000);
    imu.init();
    MD.setVelocityZero();
    initModeRun();
    imu.setZero();
    // timer.start();
}

int main(void) {
    setup();
    while (1) {
        // timer.reset();
        modeRun();
        // pc.printf("interval:%dus\r\n",timer.read_us());
    }
}