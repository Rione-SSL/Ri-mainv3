#ifndef _MODES_
#define _MODES_
// modes
#include "modeTest.h"
#include "modeMain.h"
#include "modeTestIMU.h"

// mode registration
const int8_t modeIndex = 3;
const RIMode modes[modeIndex] = {modeMain, modeTest, modeTestIMU};

#endif