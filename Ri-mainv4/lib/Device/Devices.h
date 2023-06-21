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
#include "PID.h"
#include "LPF.h"

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
    PID attitudePID;
    PID angulerVelocityPID;
    LPF velocityLPF;

    Devices();

    void init();

    void getSensors(RobotInfo &info);
    float getAngularVelocity(float prev, float now);
    int16_t getAttitudeCtrl(RobotInfo &info);
    int16_t getAngulerVelocityCtrl(RobotInfo &info, float targetVelocity);

  private:
    Timer timer;
    float prevDir;
};

extern Devices devices;

#endif