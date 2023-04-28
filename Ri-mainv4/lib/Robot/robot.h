#ifndef ROBOT_H
#define ROBOT_H

#include <mbed.h>

class Robot {
  public:
    Robot();
    void setup();
    void loop();

  private:
    RawSerial pc;
};

#endif