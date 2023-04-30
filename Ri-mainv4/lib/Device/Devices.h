#ifndef DEVICES_H
#define DEVICES_H

#include <mbed.h>
#include "Ball.h"
#include "Dribbler.h"
#include "Motor.h"
#include "LGIMU.h"
#include "LGKIcker.h"
#include "RaspSerial.h"
#include "Battery.h"

#include "RobotInfo.h"

class Devices {
  public:
    Serial pc;
    I2C i2c;
    raspSerial rasp;
    Ball ball;
    LGKicker kickerStraight;
    LGKicker kickerChip;
    Dribbler dribbler;
    Motor MD;
    BNO055 imu;
    DigitalOut LED;
    Battery battery;

    Devices();

    void init();

    void getSensors(RobotInfo &info);
};

extern Devices devices;

#endif