#ifndef _MODETEST_
#define _MODETEST_

#include "setup.h"

void before_test() {
    // bodyを実行する直前に1度だけ実行する関数
    pc.printf("before test\r\n");
    imu.setZero();
}
// モードのメインプログラムを書く関数.この関数がループで実行されます
void body_test() {
    int16_t m_turn = 0;
    getSensors(info);
    if (info.imuStatus == IMU_RESET) {
        imu.setZero();
    }
    if (!info.emergency) {
        // MD.setMotors(info,0,0,0,0);//motorのpower
        pidDir.target = info.imuTargetDir;
        pidDir.rawData = info.imuDir;
        m_turn = getTurnAttitude();
        MD.setVelocity(info, m_turn);
        if (info.kickerPower[STRAIGHT_KICKER] > 0) {
            kicker[STRAIGHT_KICKER].setPower(info.kickerPower[STRAIGHT_KICKER]);
            kicker[STRAIGHT_KICKER].Kick();
        }
        if (info.kickerPower[CHIP_KICKER] > 0) {
            kicker[CHIP_KICKER].setPower(info.kickerPower[CHIP_KICKER]);
            kicker[CHIP_KICKER].Kick();
        }
        dribler.write(info.driblePower); // power:0.0~1.0
    } else {
        pc.printf("emergency!!!\t");
        MD.setVelocityZero();
        kicker[STRAIGHT_KICKER].setPower(0.0);
        kicker[CHIP_KICKER].setPower(0.0);
        dribler.write(0);
    }
    rasp.sendToRasp(info);
    pc.printf("M1:%d\tM2:%d\tM3:%d\tM4:%d\tdrib:%.2f\tstraight:%.2f\tchip:"
              "%.2f\tvolt:%d\tPhoto:%d\timu:%.02f\ttargetDeg:%02f\temg:%d\tinterval:%dus\r\n",
              info.motor[0], info.motor[1], info.motor[2], info.motor[3],
              info.driblePower, info.kickerPower[STRAIGHT_KICKER],
              info.kickerPower[CHIP_KICKER], info.volt, info.photoSensor,
              info.imuDir, info.imuTargetDir, info.emergency, timer.read_us());
}

void after_test() {
    // モードが切り替わり、bodyが実行し終えた直後に1度だけ実行する関数
    pc.printf("after test\r\n");
    dribler.write(0);
    MD.setVelocityZero();
}

const RIMode modeTest = {
    modeName : "mode_test", //モードの名前.コンソールで出力したりLCDに出せます.
    modeLetter : 'T',       //モード実行のコマンド
    before : callback(before_test),
    body : callback(body_test),
    after : callback(after_test)
};

#endif