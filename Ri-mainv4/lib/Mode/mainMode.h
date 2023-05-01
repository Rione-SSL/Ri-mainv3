#ifndef MAIN_H
#define MAIN_H

#include "Mode.h"
#include "Devices.h"
class MainMode : public Mode {
  public:
    MainMode(char letter, const char name[]) : Mode(letter, name) {}
    void init() {
        devices.pc.printf("Resistored : '%c' as %s\n", getModeLetter(), getModeName());
    }
    void before() {
        devices.pc.printf("before MainMode\n");
        devices.imu.setZero();
        devices.attitudePID.reset();
    }
    void loop() {
        devices.getSensors(info);
        int16_t m_turn = devices.getAttitudeCtrl(info);
        if (IMU_CALIBURATION) {
            devices.MD.setVelocityZero();
        } else {
            devices.MD.setVelocity(info, m_turn);
        }

        if (info.isHoldBall) {
            devices.dribbler.setPower(info.driblePower);
            if (info.kickerPower[STRAIGHT_KICKER] > 0) {
                devices.kickerStraight.setPower(info.kickerPower[STRAIGHT_KICKER]);
                devices.kickerStraight.Kick();
                devices.dribbler.turnOff();
            } else {
                if (info.kickerPower[CHIP_KICKER] > 0) {
                    devices.kickerChip.setPower(info.kickerPower[CHIP_KICKER]);
                    devices.kickerChip.Kick();
                    devices.dribbler.turnOff();
                } else {
                    devices.dribbler.dribble();
                }
            }
        } else {
            if (info.driblePower != 0) {
                devices.dribbler.setPower(0.3);
            } else {
                devices.dribbler.setPower(0.0);
            }
            devices.dribbler.dribble();
        }
        devices.rasp.send(info);
        devices.MD.setMotors(info, m_turn, m_turn, m_turn, m_turn);
    }
    void after() {
        devices.pc.printf("after MainMode\n");
        devices.dribbler.turnOff();
        devices.MD.setVelocityZero();
    }

  private:
};

extern MainMode mainMode;

#endif