#ifndef MODE_H
#define MODE_H
#include <mbed.h>

class Mode {
  public:
    Mode(char letter, const char name[]) : modeLetter(letter) {
        strcpy(modeName, name);
    }

    char *getModeName() {
        return modeName;
    }

    char getModeLetter() {
        return modeLetter;
    }

    virtual void init() {
        devices.pc.printf("Resistored : '%c' as %s\n", getModeLetter(), getModeName());
    };
    virtual void before() {
        devices.pc.printf("before %s\n", getModeName());
        devices.imu.setZero();
        devices.attitudePID.reset();
    };
    virtual void loop() {
        devices.pc.printf("loop %s\n", getModeName());
    };
    virtual void after() {
        devices.pc.printf("after %s\n", getModeName());
        devices.dribbler.turnOff();
        devices.MD.setVelocityZero();
    };

  protected:
    char modeName[24];
    char modeLetter;
};

#endif