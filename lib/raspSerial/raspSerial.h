#ifndef _RASPSERIAL_
#define _RASPSERIAL_

#include "mbed.h"
#include "RobotInfo.h"

class raspSerial {
  public:
    raspSerial(PinName TX, PinName RX);
    raspSerial(PinName TX, PinName RX, int baud);
    void receiveRx();
    void put(int val);
    void get(float &a, int num);
    void print(float val);
    void syncFromRasp(RobotInfo &_info);
    void sendToRasp(RobotInfo info);

  private:
    static const int8_t BUFFER_SIZE = 9;
    //ここ元々intだったのですが8bitの変数しか扱えない空間でint(32bit)はアウトなのでuint8_tにしておきます。
    uint8_t buffer[64];
    RawSerial device;
    int8_t bufferCount;

    RobotInfo info = {
      .motor = {0, 0, 0, 0},
      .driblePower = 0,
      .kickerPower = {0, 0},
      .volt = 0,
      .photoSensor = 0,
      .isHoldBall = 0,
      .imuDir = 0,
      .emergency = 0, 
    };
};

#endif