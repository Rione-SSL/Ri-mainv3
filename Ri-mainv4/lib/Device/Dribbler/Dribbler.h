#ifndef DRIBBLER_H
#define DRIBBLER_H
#include "mbed.h"
#include "Servo.h"
class Dribbler {
  public:
    Dribbler(PinName dribblerPin);
    void setPower(float p);
    void setAccelerationStep(uint8_t interval);
    void disableAcceleration();

    void dribble();
    void turnOff();
    float getPower();

  private:
    Servo motor;
    float targetPower;
    float targetPowerPrev;
    float power;
    uint8_t accelerationStep;
    Timer timer;
    Timer offTimer;
    bool accelerrationEnabled;
};

#endif
