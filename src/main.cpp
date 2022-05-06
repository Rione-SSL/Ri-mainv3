#include "mbed.h"
#include "modeRun.h"

void setup() {
    swDrible.mode(PullUp);
    swKicker.mode(PullUp);
    pc.baud(2000000);
    initModeRun();
}

int main(void) {
    setup();
    while (1) {
        modeRun();
    }
}