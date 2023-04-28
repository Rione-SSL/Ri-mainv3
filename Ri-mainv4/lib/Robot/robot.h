#ifndef ROBOT_H
#define ROBOT_H

#include <mbed.h>
#include "Devices.h"
#include "Mode.h"

#include "mainMode.h"

class Robot {
  public:
    Robot();
    void setup();
    void loop();

  private:
    // Devices devices;
};

#endif