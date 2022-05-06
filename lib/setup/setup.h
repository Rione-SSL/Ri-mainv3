#ifndef _SETUP_H_
#define _SETUP_H_

#include "mbed.h"
#include "pinDefs.h"
#include "setup_common.h"
#include "RIMode.h"
#include "Servo.h"

// Serial
Serial pc(USBTX, USBRX, 2000000);
// Drive drive(CAN_TX, CAN_RX);

// signals
AnalogIn ballPhoto(BALL_PHOTOSENS);
DigitalOut raspBallDetectSig(RASPI_SIG);
DigitalOut LED(LED1);

// PwmOut kick(D9);
// LGKicker kicker(KICKER_KICK);
Servo dribler(DRIB_PWM);

// for test
DigitalIn swDrible(TEST_DRIB);
DigitalIn swKicker(TEST_KICK);

char mode;               // mode letter
int8_t runningModeIndex; // mode index
int8_t runningModeIndexPrev;

RIMode target;
RIMode targetPrev;

#endif