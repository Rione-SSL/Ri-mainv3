#include "mbed.h"
#include "modeRun.h"

void setup() {
    swDrible.mode(PullUp);
    swKicker.mode(PullUp);
    pc.baud(2000000);
    imu.init();
    for (size_t i = 0; i < 30; i++) {
        imu.setZero();
    }
    initModeRun();
}

int main(void) {
    setup();
    while (1) {
        modeRun();
    }
}