#ifndef MAIN_H
#define MAIN_H

#include "Mode.h"
#include "Devices.h"
class MainMode : public Mode {
  public:
    MainMode(char letter, const char name[]) : Mode(letter, name) {}
    void init() {
        devices.pc.printf("Resistored : '%c' as %s\n", getModeLetter(), getModeName());
    }
    void before() {
        devices.pc.printf("before MainMode\n");
    }
    void loop() {
        devices.pc.printf("loop MainMode\n");
    }
    void after() {
        devices.pc.printf("after MainMode\n");
    }

  private:
};

extern MainMode mainMode;

#endif