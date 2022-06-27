#ifndef _MODE_TEST_IMU_
#define _MODE_TEST_IMU_

#include "setup.h"

void before_test_imu() {
    pc.printf("before test imu\r\n");
    imu.setZero();
}

void body_test_imu() {
    info.imuDir = imu.getDeg();
    pidDir.target = 0;
    pidDir.rawData = info.imuDir;

    int16_t m_power = getTurnAttitude();
    pc.printf("imu:%f %d %f\r\n", pidDir.currentData, m_power, pidDir.totalError);
    MD.setMotors(info, m_power, m_power, m_power, m_power);
}

void after_test_imu() {
    pc.printf("after test imu\r\n");
    MD.setVelocityZero();
}

const RIMode modeTestIMU = {
    modeName : "mode_test_imu",
    modeLetter : 'I',
    before : callback(before_test_imu),
    body : callback(body_test_imu),
    after : callback(after_test_imu)
};

#endif