#ifndef MAIN_H
#define MAIN_H
#include <mbed.h>
#include <Mode.h>

class MainMode : public Modes {
  public:
    MainMode();
    void before();
    void loop();
    void after();

  private:
    RawSerial *pc;
};

#endif