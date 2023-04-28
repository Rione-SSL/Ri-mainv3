#ifndef ROBOT_H
#define ROBOT_H

#include <mbed.h>
#include "Devices.h"
#include "Mode.h"

#define MODE_QTY 1

#include "mainMode.h"
extern Mode modes[];
class Robot {
  public:
    Robot();
    void setup();
    void loop();

  private:
    // Devices devices;
};

#endif