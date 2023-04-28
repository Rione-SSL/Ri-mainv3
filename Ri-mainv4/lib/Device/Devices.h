#ifndef DEVICES_H
#define DEVICES_H

#include <mbed.h>
#include "Dribbler.h"
#include "Motor.h"
#include "LGIMU.h"
#include "LGKIcker.h"
#include "RaspSerial.h"

#include "RobotInfo.h"

class Devices {
  public:
    RawSerial pc;
    I2C i2c;
    RaspSerial raspSerial;
    LGKicker kickerStraight;
    LGKicker kickerChip;
    Dribbler dribbler;
    Motor MD;
    BNO055 imu;
    DigitalOut LED;
    AnalogIn voltIn;

    Devices()
        : pc(USBTX, USBRX, BAUDLATE),
          i2c(I2C_SDA, I2C_SCL),
          raspSerial(RASP_TX, RASP_RX, &pc, 9600),
          kickerStraight(KICKER_STRAIGHT),
          kickerChip(KICKER_CHIP),
          dribbler(DRIB_PWM),
          MD(CAN_TX, CAN_RX, MOTOR_TEST_SW),
          imu(&i2c),
          LED(LED1),
          voltIn(VOLT_IN){};
    void init();
};

#endif