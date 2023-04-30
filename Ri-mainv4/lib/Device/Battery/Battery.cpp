#include "Battery.h"

Battery::Battery(PinName __pin, uint16_t _threshould)
    : _pin(__pin, PullDown), pin(__pin),
      threshould(_threshould), batteryVoltage(0),
      counter(0), isBatteryLow(false) {
}

float Battery::getVoltage() {
    uint16_t v_d = pin.read_u16();
    batteryVoltage = (4.9E-09 * v_d * v_d + 0.0028 * v_d - 33);
    checkBattery();
    return batteryVoltage;
}

void Battery::checkBattery() {
    if (batteryVoltage < threshould) {
        counter++;
    } else {
        counter--;
    }
    counter = Constrain(counter, 0, 300);
    isBatteryLow = counter > 300;
}

bool Battery::isLow() {
    return isBatteryLow;
}