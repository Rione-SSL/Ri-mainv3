#include <robot.h>

MainMode mainMode('m', "MainMode");
Mode *modes[] = {
    &mainMode};

Robot::Robot() {
}

void Robot::setup() {
    devices.pc.baud(BAUDLATE);
    devices.pc.printf("Hello World!\n");
    for (int i = 0; i < MODE_QTY; i++) {
        modes[i]->init();
    }
}

void Robot::loop() {
    modes[0]->loop();
    // mainMode.loop();
}
