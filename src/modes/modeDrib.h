#ifndef _MODEDRIB_
#define _MODEDRIB_

#include "setup.h"

void before_drib() {
    // bodyを実行する直前に1度だけ実行する関数
    pc.printf("before driber test\r\n");
}

void body_drib() {
    // モードのメインプログラムを書く関数.この関数がループで実行されます
    float p = 0.2;
    dribler.write(p);
    pc.printf("drib power:%f\r\n", p);
}

void after_drib() {
    // モードが切り替わり、bodyが実行し終えた直後に1度だけ実行する関数
    pc.printf("after driber test\r\n");
    dribler.write(0.0);
}

const RIMode modeDrib = {
    modeName :
        "mode_drib_test", //モードの名前.コンソールで出力したりLCDに出せます.
    modeLetter : 'D', //モード実行のコマンド
    before : callback(before_drib),
    body : callback(body_drib),
    after : callback(after_drib)
};

#endif