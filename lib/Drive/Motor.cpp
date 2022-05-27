#include "Motor.h"
#define MOTOR_TEST_IGNORE
Motor::Motor(PinName CAN_TX, PinName CAN_RX, PinName testSW)
    : canMBED(CAN_TX, CAN_RX), switch_1(testSW) {
    canMBED.frequency(100000);
}

void Motor::setVelocity(RobotInfo &info) {
    if (switch_1.read() == 0) {
#ifndef MOTOR_TEST_IGNORE
        order.M1.vel = 20;
        order.M2.vel = 20;
        order.M3.vel = 20;
        order.M4.vel = 20;
#endif
    } else {
        order.M1.vel = info.motor[0];
        order.M2.vel = info.motor[1];
        order.M3.vel = info.motor[2];
        order.M4.vel = info.motor[3];
    }
    sendMotorValues();
}

void Motor::setVelocityZero() {
    order.M1.vel = 0;
    order.M2.vel = 0;
    order.M3.vel = 0;
    order.M4.vel = 0;
    sendMotorValues();
}

void Motor::sendMotorValues() {
    send_motvel_data[0] = order.M1.vel8_t.L;
    send_motvel_data[1] = order.M1.vel8_t.H;
    send_motvel_data[2] = order.M2.vel8_t.L;
    send_motvel_data[3] = order.M2.vel8_t.H;
    send_motvel_data[4] = order.M3.vel8_t.L;
    send_motvel_data[5] = order.M3.vel8_t.H;
    send_motvel_data[6] = order.M4.vel8_t.L;
    send_motvel_data[7] = order.M4.vel8_t.H;
    canMBED.write(CANMessage(0x1AA, send_motvel_data, 8));
}
