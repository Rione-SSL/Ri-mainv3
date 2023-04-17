#ifndef ATTITUDE_H
#define ATTITUDE_H
#include "mbed.h"

typedef struct {
    float rawData;  //コンパスのデータ
    float last_currentData; //前回
    float last_differential;
    float currentData;
    float out;
    float pid_out;
    float last_out;
    int16_t target;     //目標点
    int16_t targetPrev; //目標点
    float differential;
    float second_differential;

    float totalError;
    float Ki;
    float Kd;
    float Kp;

    float P;
    float I;
    float D;
    int16_t turn;
} type_pid;

Ticker tickCalcIMU;
Timer pidDt;
type_pid pidDir;

bool imuDirEnable = true;
int16_t degBetween(int16_t deg1, int16_t deg2) {
    int16_t a = deg1 - deg2;
    while (a < 0)
        a += 360;
    while (a > 180)
        a -= 360;
    return abs(a);
}

int16_t degBetween_signed(int16_t deg1, int16_t deg2) {
    int16_t a = deg1 - deg2;
    while (a < -180)
        a += 360;
    while (a > 180)
        a -= 360;
    return a;
}

void setTargetDir(int16_t target) {
    pidDir.target = target;
}

void setPIDGain() {
    pidDir.Kp = 0.4;
    pidDir.Ki = 0.3;
    pidDir.Kd = 0.01;
}

void attitudeControl() {
    if (imuDirEnable) {
        pidDir.currentData = degBetween_signed(pidDir.target, pidDir.rawData);
        pidDir.differential = (pidDir.currentData - pidDir.last_currentData) / 0.006;
        pidDir.second_differential=(pidDir.differential - pidDir.last_differential) / 0.006;
        pidDir.last_currentData = pidDir.currentData;
        pidDir.last_differential=pidDir.differential;

        pidDir.P = pidDir.Kp * pidDir.differential;
        pidDir.I = pidDir.Ki * pidDir.currentData;
        pidDir.D = pidDir.Kd * pidDir.second_differential;

        pidDir.pid_out = pidDir.P + pidDir.I + pidDir.D;
        pidDir.out = pidDir.last_out+pidDir.pid_out * 0.006;
        //pidDir.last_out=pidDir.out;
        if (abs(pidDir.out) > 25) {
            pidDir.out = pidDir.out / abs(pidDir.out) * 25;
        }
        pidDir.last_out=pidDir.out;
        pidDir.targetPrev = pidDir.target;
        pidDir.turn = pidDir.out;
    }
}

int16_t getTurnAttitude() {
    return pidDir.turn;
}
#endif