#include "Ball.h"

Ball::Ball(PinName _pin, PinName _ledPin, uint16_t _threshold)
    : sensor(_pin),
      LED(_ledPin),
      isHoldBall(false),
      sensorValue(0),
      threshold(_threshold) {
}

void Ball::setThreshold(uint16_t _threshold) {
    threshold = _threshold;
}

uint16_t Ball::getSensor() {
    sensorValue = sensor.read_u16() / 65.535; // 0~1000に変換
    isHoldBall = (sensorValue < threshold);
    LED = isHoldBall;
    return sensorValue;
}

bool Ball::getState() {
    return isHoldBall;
}