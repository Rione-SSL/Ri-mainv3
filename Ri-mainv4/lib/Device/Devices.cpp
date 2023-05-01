#include "Devices.h"

RobotInfo info;
Devices devices;
asm(".global _printf_float"); // enables float printing

Devices::Devices()
    : pc(USBTX, USBRX, BAUDLATE),
      i2c(I2C_SDA, I2C_SCL),
      rasp(RASP_TX, RASP_RX, &pc, 9600),
      ball(BALL_PHOTOSENS, RASPI_SIG, BALL_DETECT_VALUE),
      kickerStraight(KICKER_STRAIGHT),
      kickerChip(KICKER_CHIP),
      dribbler(DRIB_PWM),
      MD(CAN_TX, CAN_RX, MOTOR_TEST_SW),
      imu(&i2c),
      LED(LED1),
      battery(VOLT_IN, BATTERY_THRESHOLD){};

void Devices::init() {
    i2c.frequency(400000);
    imu.init();
    MD.setMotors(info, 0, 0, 0, 0);
    ball.setThreshold(BALL_DETECT_VALUE);
}
void Devices::getSensors(RobotInfo &info) {
    rasp.syncFromRasp(info);
    info.photoSensor = ball.getSensor();
    info.isHoldBall = ball.getState();
    info.imuDirPrev = info.imuDir;
    info.imuDir = imu.getDeg();
    info.volt = battery.getVoltage();
    info.isLowBattery = battery.isLow();
}