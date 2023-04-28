#ifndef MODES_H
#define MODES_H
#include <mbed.h>

class Modes {
  public:
    char getModeName() {
        return *modeName;
    }
    char getModeLetter() {
        return modeLetter;
    }
    void setModeName(char *name, char letter) {
        strcpy(modeName, name);
        modeLetter = letter;
    }
    virtual void before();
    virtual void loop();
    virtual void after();

  private:
    char modeName[24];
    char modeLetter;
};

#endif