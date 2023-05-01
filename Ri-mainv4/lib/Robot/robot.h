#ifndef ROBOT_H
#define ROBOT_H

#include <mbed.h>
#include "Devices.h"
#include "Mode.h"

#define MODE_QTY 1
extern Mode *modes[MODE_QTY];

#include "mainMode.h"

class Robot {
  public:
    Robot();
    void setup();
    void loop();

  private:
    char modeLetter;
    Mode *currentMode;
    Mode *prevMode;

    char buffer[64];
    volatile bool data_received;

    void pcRxIrq();
    void doCommand(const char command[]);
};

#endif