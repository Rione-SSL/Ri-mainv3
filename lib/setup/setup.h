#ifndef _SETUP_H_
#define _SETUP_H_

#include "mbed.h"
#include "pinDefs.h"
#include "setup_common.h"
#include "RIMode.h"

// Libs
#include "Servo.h"
#include "LGKicker.h"
#include "raspSerial.h"
#include "Motor.h"
#include "RobotInfo.h"
#include "LGIMU.h"

// Serial
asm(".global _printf_float"); // enables float print
Serial pc(USBTX, USBRX, 2000000);
raspSerial rasp(RASP_TX, RASP_RX);

Motor MD(CAN_TX, CAN_RX, MOTOR_TEST_SW);
I2C i2c(I2C_SDA, I2C_SCL);
BNO055 imu(&i2c);

// signals
AnalogIn ballPhoto(BALL_PHOTOSENS);
DigitalOut raspBallDetectSig(RASPI_SIG);
DigitalOut LED(LED1);

LGKicker kicker[2] = {KICKER_STRAIGHT, KICKER_CHIP};
Servo dribler(DRIB_PWM);

// for test
DigitalIn swDrible(TEST_DRIB);
DigitalIn swKicker(TEST_KICK);

// mode management
char mode;               // mode letter
int8_t runningModeIndex; // mode index
int8_t runningModeIndexPrev;
RIMode target;
RIMode targetPrev;
RobotInfo info;

#endif