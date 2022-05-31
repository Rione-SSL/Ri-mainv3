
#ifndef _RIHARDWARE_API_
#define _RIHARDWARE_API_

// Libs
#include "Servo.h"
#include "LGKicker.h"
#include "raspSerial.h"
#include "Motor.h"
#include "RobotInfo.h"
#include "LGIMU.h"

#include "pinDefs.h"
#include "setup_common.h"
#include "mbed.h"

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

DigitalIn _voltIn(VOLT_IN, PullDown);
AnalogIn voltIn(VOLT_IN);

// Write Hardware API Fuctions under hear
uint8_t readBatteryVoltage() {
    uint16_t v_d = voltIn.read_u16();
    return (4.9E-09 * v_d * v_d + 0.0028 * v_d - 33);
}

#endif