#include <robot.h>

Mode modes[] = {
    MainMode('m', "MainMode")};

Robot::Robot() {}

void Robot::setup() {
    modes[0].init();
}

void Robot::loop() {
    modes[0].loop();
}
