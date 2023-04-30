#ifndef BALL_H
#define BALL_H

#include <mbed.h>

class Ball {
  private:
    /* data */
    AnalogIn sensor;
    DigitalOut LED;
    bool isHoldBall;
    uint16_t sensorValue;
    uint16_t threshold;

  public:
    Ball(PinName _pin, PinName _ledPin, uint16_t _threshold = 600);
    void setThreshold(uint16_t _threshold);
    uint16_t getSensor();
    void setTthreshold(uint16_t _threshold);
    bool getState();
};

#endif