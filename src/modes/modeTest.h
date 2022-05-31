#ifndef _MODETEST_
#define _MODETEST_

#include "setup.h"

void before_test() {
    // bodyを実行する直前に1度だけ実行する関数
    pc.printf("before test\r\n");
}

void body_test() {
    // モードのメインプログラムを書く関数.この関数がループで実行されます
    uint16_t v_d = voltIn.read_u16();
    info.volt = 4.9E-09 * v_d * v_d + 0.0028 * v_d - 33;
    pc.printf("volt:%d\r\n", info.volt);
}

void after_test() {
    // モードが切り替わり、bodyが実行し終えた直後に1度だけ実行する関数
    pc.printf("after test\r\n");
}

const RIMode modeTest = {
    modeName : "mode_test", //モードの名前.コンソールで出力したりLCDに出せます.
    modeLetter : 'T', //モード実行のコマンド
    before : callback(before_test),
    body : callback(body_test),
    after : callback(after_test)
};

#endif