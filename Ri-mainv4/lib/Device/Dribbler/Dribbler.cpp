#include "mbed.h"
#include "Dribbler.h"

Dribbler::Dribbler(PinName dribblerPin)
    : motor(dribblerPin),
      targetPower(1.0),
      targetPowerPrev(0.0),
      power(0.0),
      accelerationStep(15),
      accelerrationEnabled(false) {
    timer.start();
    offTimer.start();
}

void Dribbler::setPower(float p) {
    targetPowerPrev = targetPower;
    targetPower = (p < 0.0 ? 0.0 : (p > 1.0 ? 1.0 : p));
    if (targetPower < targetPowerPrev) offTimer.reset();
}

void Dribbler::setAccelerationStep(uint8_t interval) {
    if (interval == 0) {
        accelerrationEnabled = false;
        return;
    }
    accelerationStep = interval;
    accelerrationEnabled = true;
}

void Dribbler::disableAcceleration() {
    accelerrationEnabled = false;
}

void Dribbler::dribble() {
    if (accelerrationEnabled) {
        if (targetPower >= 0.0) {
            if (power < targetPower) {
                if (timer.read_ms() > accelerationStep) {
                    power += 0.02;
                    timer.reset();
                }
            } else {
                if (offTimer.read_ms() > 600) power = targetPower;
            }
        } else {
            targetPower = 0;
            power = 0;
        }
        motor.write(power);
    } else {
        motor.write(targetPower);
    }
}

void Dribbler::turnOff() {
    motor.write(0);
    power = 0;
}

float Dribbler::getPower() {
    return power;
}