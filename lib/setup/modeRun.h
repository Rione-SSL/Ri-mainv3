#ifndef _MODERUN_
#define _MODERUN_

#include "setup.h"

INLINE void modeRun() {
    pc.printf("hello world\r\n");
    wait_ms(100);
}

#endif