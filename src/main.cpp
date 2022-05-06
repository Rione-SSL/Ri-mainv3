#include "mbed.h"
#include "modeRun.h"

void setup() {
    swDrible.mode(PullUp);
    swKicker.mode(PullUp);
    initModeRun();
}

int main(void) {
    setup();
    while (1) {
        modeRun();
    }
}