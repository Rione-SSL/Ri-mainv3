#include "Ball.h"

Ball::Ball(PinName _pin, PinName _ledPin, uint16_t _threshold, int _dulation)
    : sensor(_pin),
      LED(_ledPin),
      isHoldBall(false),
      sensorValue(0),
      threshold(_threshold),
      dulation((uint32_t)_dulation),
      timer() {
    timer.start();
}

void Ball::setThreshold(uint16_t _threshold) {
    threshold = _threshold;
}

uint16_t Ball::getSensor() {
    sensorValue = sensor.read_u16() / 65.535; // 0~1000に変換
    if (sensorValue < threshold) {
        isHoldBall = true;
        timer.reset();
    } else {
        if (timer.read_ms() < dulation) {
            isHoldBall = true;
        } else {
            isHoldBall = false;
        }
    }
    LED = isHoldBall;
    return sensorValue;
}

bool Ball::getState() {
    return isHoldBall;
}
