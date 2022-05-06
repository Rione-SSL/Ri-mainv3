#ifndef _MODEMAIN_
#define _MODEMAIN_

#include "setup.h"

Timeout dribTimeout;

void dribleOff() {
    // タイマー割り込みでドリブルをオフにする
    dribler.write(0);
}

void before_main() {
    // bodyを実行する直前に1度だけ実行する関数
    pc.printf("before main\r\n");
}

void body_main() {
    // モードのメインプログラムを書く関数.この関数がループで実行されます
    // dribler test
    if (swDrible.read() == false) {
        dribTimeout.attach(dribleOff, 1);
        dribler.write(1.0);
    }

    // kicker test
    if (swKicker.read() == false) {
        kicker.Kick();
    }
    raspBallDetectSig = LED = (ballPhoto.read() < BALL_DETECT_VALUE);
}

void after_main() {
    // モードが切り替わり、bodyが実行し終えた直後に1度だけ実行する関数
    pc.printf("after main\r\n");
    dribler.write(0);
}

const RIMode modeTest = {
    modeName : "mode_test", //モードの名前.コンソールで出力したりLCDに出せます.
    modeLetter : 'M', //モード実行のコマンド
    before : callback(before_main),
    body : callback(body_main),
    after : callback(after_main)
};

#endif