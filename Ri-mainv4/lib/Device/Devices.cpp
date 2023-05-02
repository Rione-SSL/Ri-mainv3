#include "Devices.h"

RobotInfo info;
Devices devices;
asm(".global _printf_float"); // enables float printing

Devices::Devices()
    : pc(USBTX, USBRX, BAUDLATE),
      i2c(I2C_SDA, I2C_SCL),
      rasp(RASP_TX, RASP_RX, &pc, RASP_BAUDRATE),
      ball(BALL_PHOTOSENS, RASPI_SIG, BALL_DETECT_VALUE),
      kickerStraight(KICKER_STRAIGHT),
      kickerChip(KICKER_CHIP),
      dribbler(DRIB_PWM),
      MD(CAN_TX, CAN_RX, MOTOR_TEST_SW),
      imu(&i2c),
      LED(LED1),
      battery(VOLT_IN, BATTERY_THRESHOLD),
      attitudePID(IMU_KP, IMU_KI, IMU_KD, IMU_PERIOD, &pc){};

void Devices::init() {
    i2c.frequency(400000);
    imu.init();
    imu.setZero();
    dribbler.turnOff();
    MD.setVelocityZero();
    ball.setThreshold(BALL_DETECT_VALUE);
    attitudePID.reset();
}

// センサ値取得
void Devices::getSensors(RobotInfo &info) {
    rasp.sync(info);
    info.photoSensor = ball.getSensor();
    info.isHoldBall = ball.getState();
    info.imuDirPrev = info.imuDir;
    // info.imuDir = imu.getDeg();
    info.volt = battery.getVoltage();
    info.isLowBattery = battery.isLow();
}

// 姿勢制御
int16_t Devices::getAttitudeCtrl(RobotInfo &info) {
    attitudePID.appendError(gapDegrees180(info.imuTargetDir, info.imuDir));
    return (int16_t)(attitudePID.getPID());
    return 1;
}