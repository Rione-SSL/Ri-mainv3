#ifndef _MODETEST_
#define _MODETEST_

#include "setup.h"

void before_test() {
    // bodyを実行する直前に1度だけ実行する関数
    pc.printf("before test\r\n");
}

void body_test() {
    // モードのメインプログラムを書く関数.この関数がループで実行されます
    // info.volt = readBatteryVoltage();
    // getSensors(info);
    // pc.printf("volt:%d\r\n", info.imuTargetDir);
    // pc.printf("%d\r\n",rasp.recievedData);
    rasp.sendToRasp(info);
    getSensors(info);
    if (!info.emergency) {
        // MD.setMotors(info,0,0,0,0);//motorのpower
        MD.setVelocity(info);
        if (info.kickerPower[STRAIGHT_KICKER] > 0) {
            kicker[STRAIGHT_KICKER].setPower(info.kickerPower[STRAIGHT_KICKER]);
            kicker[STRAIGHT_KICKER].Kick();
        }
        // if(info.kickerPower[CHIP_KICKER] > 0){
        //     kicker[CHIP_KICKER].setPower(info.kickerPower[CHIP_KICKER]);
        //     kicker[CHIP_KICKER].Kick();
        // }
        dribler.write(info.driblePower); // power:0.0~1.0
    } else {
        // pc.printf("emergency!!!\t");
        MD.setVelocityZero();
        kicker[STRAIGHT_KICKER].setPower(0.0);
        kicker[CHIP_KICKER].setPower(0.0);
        dribler.write(0);
    }
}

void after_test() {
    // モードが切り替わり、bodyが実行し終えた直後に1度だけ実行する関数
    pc.printf("after test\r\n");
}

const RIMode modeTest = {
    modeName : "mode_test", //モードの名前.コンソールで出力したりLCDに出せます.
    modeLetter : 'T',       //モード実行のコマンド
    before : callback(before_test),
    body : callback(body_test),
    after : callback(after_test)
};

#endif