#ifndef _MODEKICK_
#define _MODEKICK_

#include "setup.h"

void before_kick() { pc.printf("before Kicker Test\r\n"); }

void body_kick() {
    float p = 1.0;
    getSensors(info);
    pc.printf("sens:%d\r\n", info.photoSensor);
    if (info.isHoldBall) {
        kicker[CHIP_KICKER].setPower(p); // power:0.0~1.0
        kicker[CHIP_KICKER].Kick();
    }
}

void after_kick() {
    pc.printf("after Kicker Test\r\n");
    kicker[STRAIGHT_KICKER].setPower(0);
    kicker[CHIP_KICKER].setPower(0);
}

const RIMode modeKick = {
    modeName :
        "mode_kick_test", //モードの名前.コンソールで出力したりLCDに出せます.
    modeLetter : 'K', //モード実行のコマンド
    before : callback(before_kick),
    body : callback(body_kick),
    after : callback(after_kick)
};

#endif