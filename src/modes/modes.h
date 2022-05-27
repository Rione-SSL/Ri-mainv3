#ifndef _MODES_
#define _MODES_
// modes
#include "modeTest.h"
#include "modeMain.h"
#include "modeTestIMU.h"
#include "modeDrib.h"

// mode registration
const int8_t modeIndex = 4;
const RIMode modes[modeIndex] = {modeMain, modeTest, modeTestIMU, modeDrib};

#endif