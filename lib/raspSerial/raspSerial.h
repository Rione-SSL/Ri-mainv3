#ifndef _RASPSERIAL_
#define _RASPSERIAL_

#include "mbed.h"
#include "robotInfo.h"

class raspSerial {
  public:
    raspSerial(PinName TX, PinName RX);
    void receiveRx();
    void put(int val);
    void get(float &a, int num);
    void print(float val);
    void syncFromRasp(robotInfo &_info);

  private:
    const int8_t BUFFER_SIZE = 7;
    int8_t buffer[64];
    RawSerial device;
    int8_t bufferCount;

    robotInfo info;
};

#endif