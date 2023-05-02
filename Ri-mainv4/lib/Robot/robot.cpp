#include <robot.h>

MainMode mainMode('M', "MainMode");

Mode *modes[MODE_QTY] = {&mainMode};

Robot::Robot()
    : modeLetter('M'),
      data_received(false) {
}

void Robot::setup() {
    devices.pc.baud(BAUDLATE);
    devices.pc.printf("Hello World!\n");
    devices.pc.printf("Boot!!\r\n");
    devices.pc.printf("\r\nHello world!! Ri-one SSL\r\n");
    devices.pc.printf("STM32 works with %ld MHz clock\r\n", (SystemCoreClock / 1000000));
    wait_ms(100);
    devices.pc.printf("-----------------------------------------------\r\n");
    devices.pc.attach(callback(this, &Robot::pcRxIrq), Serial::RxIrq);
    for (int i = 0; i < MODE_QTY; i++) {
        modes[i]->init();
    }
    prevMode = NULL;
    currentMode = NULL;
}

void Robot::loop() {
    if (data_received) {
        devices.pc.printf("%s\n", buffer);
        data_received = false;
        doCommand(buffer);
        wait(1);
    } else {
        for (size_t i = 0; i < MODE_QTY; i++) {
            if (modes[i]->getModeLetter() == modeLetter) {
                currentMode = modes[i];
                break;
            }
        }

        if (currentMode == NULL) {
            currentMode = &mainMode;
        }
        if (currentMode != prevMode) {
            if (prevMode != NULL) prevMode->after();
            currentMode->before();
        } else {
            currentMode->loop();
        }
        prevMode = currentMode;
    }
    devices.pc.printf("loop\n");
}

/*
:TODO:
- ドリブラのテスト
- モータのテスト
- フォトセンサ(ボールセンサ)のテスト
- キッカーのテスト
- PIDゲインの変更(一時的な物)
- 全てのセンサのモニタリング
*/
void Robot::doCommand(const char command[]) {
    if (strcmp(command, "hello") == 0) {
        devices.pc.printf("Hello World!\n");
    } else if (strcmp(command, "help") == 0) {
        devices.pc.printf("Commands:\n");
        for (size_t i = 0; i < MODE_QTY; i++) {
            devices.pc.printf(" - %c: %s\n", modes[i]->getModeLetter(), modes[i]->getModeName());
        }
    } else {
        devices.pc.printf("Command not found\n");
    }
}

void Robot::pcRxIrq() { // PCからの入力を受け取る
    if (devices.pc.readable()) {
        devices.pc.gets(buffer, sizeof(buffer));
        data_received = true;
    }
}
