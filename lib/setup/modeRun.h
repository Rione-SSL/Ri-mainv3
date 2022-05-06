#ifndef _MODERUN_
#define _MODERUN_

#include "setup.h"
// modes
#include "modeTest.h"
#include "modeMain.h"

// mode registration
const int8_t modeIndex = 2;
const RIMode modes[] = {modeMain, modeTest};

void receiveCommand() {
    mode = pc.getc();
    pc.printf("receive:%c\r\n", mode);
}

void initModeRun() {
    mode = 'M';
    pc.attach(&receiveCommand, Serial::RxIrq);
    wait(2);
    pc.printf("Boot!!\r\n");
    pc.printf("\r\nHello world!! Ri-one SSL\r\n");
    pc.printf("STM32 works with %ld MHz clock\r\n",
              (SystemCoreClock / 1000000));
    wait_ms(100);
    pc.printf("-----------------------------------------------\r\n");
    pc.printf("This Robots has %d modes!!\r\n", modeIndex);
    for (size_t i = 0; i < modeIndex; i++) {
        pc.printf(" -- %c : %s\r\n", modes[i].modeLetter, modes[i].modeName);
    }
    pc.printf("To run each modes, Please Type Letter like '%c'.\r\n",
              modes[0].modeLetter);
    pc.printf("-----------------------------------------------\r\n");
}

int8_t checkModeMatch(char &m) {
    for (size_t i = 0; i < modeIndex; i++) {
        if (modes[i].modeLetter == m) {
            return i;
        }
    }
    return MODE_UNMATCH;
}

void modeRun() {
    runningModeIndex = checkModeMatch(mode);
    if (runningModeIndex != MODE_UNMATCH) {
        target = modes[runningModeIndex];
        targetPrev = modes[runningModeIndexPrev];
        if (runningModeIndexPrev == runningModeIndex) {
            target.body();
        } else {
            targetPrev.after();
            target.before();
        }
    } else {
        pc.printf("Couldn't find a mode on letter:%c\r\n", mode);
        mode = modes[runningModeIndexPrev].modeLetter;
        runningModeIndex = runningModeIndexPrev;
    }

    wait_ms(100);
    runningModeIndexPrev = runningModeIndex;
}
#endif