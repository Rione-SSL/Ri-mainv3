#ifndef BATTERY_H
#define BATERY_H

#include <mbed.h>
#include <Math.h>

class Battery {
  public:
    Battery(PinName __pin, uint16_t _threshould = 132);
    float getVoltage();
    void checkBattery();
    bool isLow();

  private:
    DigitalIn _pin;
    AnalogIn pin;
    uint16_t threshould;
    float batteryVoltage;
    int16_t counter;
    bool isBatteryLow;
};

#endif