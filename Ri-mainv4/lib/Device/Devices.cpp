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
      attitudePID(IMU_KP, IMU_KI, IMU_KD, IMU_PERIOD, &pc),
      angulerVelocityPID(1, 1, 0, IMU_PERIOD, &pc),
      velocityLPF(0.01){};

void Devices::init() {
    i2c.frequency(400000);
    imu.init();
    imu.setZero();
    dribbler.disableAcceleration();
    dribbler.setAccelerationStep(DRIB_ACCELERATION_STEP);
    dribbler.turnOff();
    MD.setVelocityZero();
    ball.setThreshold(BALL_DETECT_VALUE);
    attitudePID.setLimit(30);
    attitudePID.reset();

    angulerVelocityPID.setLimit(30);
    angulerVelocityPID.reset();

    timer.start();
}

// センサ値取得
void Devices::getSensors(RobotInfo &info) {
    rasp.sync(info);
    info.photoSensor = ball.getSensor();
    info.isHoldBall = ball.getState();
    info.imuDirPrev = info.imuDir;
    info.imuDir = imu.getDeg();
    info.imuAnglerVelocity = getAngularVelocity(info.imuDirPrev, info.imuDir);
    info.volt = battery.getVoltage();
    info.isLowBattery = battery.isLow();
}

float Devices::getAngularVelocity(float prev, float now) {
    float dt = timer.read();
    timer.reset();
    // prev = normalizeDegrees(prev);
    now = normalizeDegrees(now);
    float angleDiff = prevDir - Radians(now);
    if (angleDiff > PI) {
        angleDiff -= 2 * PI;
    } else if (angleDiff < -PI) {
        angleDiff += 2 * PI;
    }
    double angularVelocity = (angleDiff / dt);

    if (abs(angleDiff) > PI && angularVelocity != 0) {
        angularVelocity += (angularVelocity > 0) ? -2 * PI / dt : 2 * PI / dt;
    }
    angularVelocity = velocityLPF.update(angularVelocity);
    prevDir = Radians(now);
    // pc.printf("vel:%.4f sh:%f dt:%f\n", angularVelocity, angleDiff, dt);
    return angularVelocity;
}

// 姿勢制御
int16_t Devices::getAttitudeCtrl(RobotInfo &info) {
    attitudePID.appendError(gapDegrees180(info.imuTargetDir, info.imuDir));
    return (int16_t)(attitudePID.getPID());
    return 1;
}

int16_t Devices::getAngulerVelocityCtrl(RobotInfo &info, float targetVelocity) {
    angulerVelocityPID.appendError(info.imuAnglerVelocity - targetVelocity);
    return (int16_t)(angulerVelocityPID.getPID());
    return 1;
}