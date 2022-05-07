#ifndef _MODETEST_
#define _MODETEST_

#include "setup.h"

void before_test() {
    // bodyを実行する直前に1度だけ実行する関数
    pc.printf("before test\r\n");
    imu.setZero();
}

void body_test() {
    // モードのメインプログラムを書く関数.この関数がループで実行されます
    info.imuDir = imu.getDeg();
    pc.printf("imu:%f\r\n", info.imuDir);
}

void after_test() {
    // モードが切り替わり、bodyが実行し終えた直後に1度だけ実行する関数
    pc.printf("after test\r\n");
}

const RIMode modeMain = {
    modeName : "mode_test", //モードの名前.コンソールで出力したりLCDに出せます.
    modeLetter : 'T', //モード実行のコマンド
    before : callback(before_test),
    body : callback(body_test),
    after : callback(after_test)
};

#endif