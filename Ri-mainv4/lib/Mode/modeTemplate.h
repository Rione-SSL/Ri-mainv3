#ifndef MAIN_H
#define MAIN_H

#include "Mode.h"
#include "Devices.h"
class ModeTemp : public Mode {
  public:
    ModeTemp(char letter, const char name[]) : Mode(letter, name) {}
    void init() {
        devices.pc.printf("Resistored : '%c' as %s\n", getModeLetter(), getModeName());
    }
    void before() {
    }
    void loop() {
    }
    void after() {
    }

  private:
};

extern ModeTemp modeTemp;

#endif