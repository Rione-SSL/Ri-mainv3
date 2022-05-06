#ifndef _MODETEST_
#define _MODETEST_

#include "setup.h"

void before_test() { pc.printf("before test\r\n"); }

void body_test() { pc.printf("body test\r\n"); }

void after_test() { pc.printf("after test\r\n"); }

const RIMode modeMain = {
    modeName : "mode_main",
    modeLetter : 'T',
    before : callback(before_test),
    body : callback(body_test),
    after : callback(after_test)
};

#endif