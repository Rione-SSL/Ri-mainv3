#ifndef _MODEMAIN_
#define _MODEMAIN_

#include "setup.h"

void before_main() { pc.printf("before main\r\n"); }

void body_main() { pc.printf("body main\r\n"); }

void after_main() { pc.printf("after main\r\n"); }

const RIMode modeTest = {
    modeName : "mode_test",
    modeLetter : 'M',
    before : callback(before_main),
    body : callback(body_main),
    after : callback(after_main)
};

#endif