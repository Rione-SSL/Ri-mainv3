#ifndef _RASPSERIAL_
#define _RASPSERIAL_

#include "mbed.h"
#include "RobotInfo.h"

class raspSerial {
  public:
    raspSerial(PinName TX, PinName RX, Serial *_pc);
    raspSerial(PinName TX, PinName RX, Serial *_pc, int baud);
    void receiveRx();
    void put(int val);
    void get(float &a, int num);
    void print(float val);
    void sync(RobotInfo &_info);
    void send(RobotInfo info);
    uint8_t buffer[64];
    uint8_t recievedData;

  private:
    static const int8_t BUFFER_SIZE = 11;
    // ここ元々intだったのですが8bitの変数しか扱えない空間でint(32bit)はアウトなのでuint8_tにしておきます。
    //  uint8_t buffer[64];
    Serial device;
    Serial *pc;
    int8_t bufferCount;
    RobotInfo info;
};

#endif