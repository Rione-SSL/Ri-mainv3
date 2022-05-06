#ifndef LGKIKCER_H
#define LGKIKCER_H
#include "mbed.h"
class LGKicker {
  public:
    LGKicker(PinName KickerPin);
    bool Kick(void);
    void setPower(float p);
    PwmOut Kicker; // DigitalOut Kicker;
    Timer timer;
    bool enabled;
    float power;

  private:
    Timeout Kicker_timeout;
    Timeout KickerIsRedey;
    void flip(void);
    void flipOn(void);
};

#endif
