#include "mbed.h"
#include "setup.h"

void setup() {
    swDrible.mode(PullUp);
    swKicker.mode(PullUp);
}

int main(void) {
    setup();
    while (1) {
        }
}