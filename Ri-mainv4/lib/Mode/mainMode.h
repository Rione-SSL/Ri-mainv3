#ifndef MAIN_H
#define MAIN_H

#include "Mode.h"
#include "Devices.h"
class MainMode : public Modes {
  public:
    MainMode(char letter, const char name[]) : Modes(letter, name) {}
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

#endif