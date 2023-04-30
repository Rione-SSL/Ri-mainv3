#include <robot.h>

MainMode mainMode('m', "MainMode");

Mode *modes[] = {
    &mainMode};

Robot::Robot() : data_received(false) {
}

void Robot::setup() {
    devices.pc.baud(BAUDLATE);
    devices.pc.printf("Hello World!\n");
    devices.pc.attach(callback(this, &Robot::pcRxIrq), Serial::RxIrq);
    for (int i = 0; i < MODE_QTY; i++) {
        modes[i]->init();
    }
}

void Robot::loop() {

    if (data_received) {
        devices.pc.printf("%s\n", buffer);
        data_received = false;
        wait(5);
    } else {
        modes[0]->loop();
    }
    // mainMode.loop();
}

void Robot::pcRxIrq() {
    if (devices.pc.readable()) {
        devices.pc.gets(buffer, sizeof(buffer));
        data_received = true;
    }
}