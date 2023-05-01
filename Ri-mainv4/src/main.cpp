#include "mbed.h"
#include <robot.h>

Robot robot;
int main(void) {
    robot.setup();
    while (true) {
        robot.loop();
    }
}