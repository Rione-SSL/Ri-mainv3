#ifndef ATTITUDE_H
#define ATTITUDE_H
#include "mbed.h"


typedef struct {
    int16_t rawData;//コンパスのデータ
    float lastData;//前回
    float currentData;//今回
    float laterData;//未来
    float out;
    float dx;//差分
    uint16_t dt;//時間差分
    int16_t target;//目標点
    float differential;//傾き,dx/dt
    float Kd;
    float Kp;
    int16_t turnDir;
} type_pid;

Ticker tickCalcIMU;
Timer pidDt;
type_pid pidDir;

bool imuDirEnable = true;

int16_t degBetween(int16_t deg1,int16_t deg2){
        int16_t a = deg1 - deg2;
        while(a < 0) a += 360;
        while(a > 180) a -= 360;
        return abs(a);
}

int16_t degBetween_signed(int16_t deg1,int16_t deg2){
        int16_t a = deg1 - deg2;
        while(a < 0) a += 360;
        while(a > 180) a -= 360;
        return a;
}

void attitudeControl(){
    if(imuDirEnable) {
        pidDir.Kp = -0.41;
        pidDir.Kd = 0.022;

        pidDir.differential = (pidDir.lastData - degBetween_signed(pidDir.rawData,pidDir.target)) / 0.006;
        if(pidDir.differential == 0.0)
            return;
        
        pidDir.out = (pidDir.Kd * pidDir.differential) + (pidDir.Kp * degBetween_signed(pidDir.rawData,pidDir.target));
        pidDir.turnDir = pidDir.out;
        pidDir.lastData = degBetween_signed(pidDir.rawData,pidDir.target);

        //pidDir.turnDir = 0;
        // if(abs(pidDir.rawData) < 40) {
        //     pidDir.Kd = -0.002;
        //     pidDir.out = -0.8*degBetween_signed(pidDir.rawData,pidDir.target);
        // }
        // else{
        //     pidDir.Kd = -0.003;
        //     pidDir.out = -1.0*degBetween_signed(pidDir.rawData,pidDir.target);;
        // }
        // pidDir.currentData = pidDir.rawData;
        // pidDir.dx = pidDir.lastData - pidDir.currentData;
        // pidDir.dt = pidDt.read_us();
        // pidDt.reset();
        // // pidDir.differential = pidDir.dx/pidDir.dt;
        // pidDir.laterData = pidDir.target - pidDir.currentData + (pidDir.dx * pidDir.dt);

        // pidDir.out = pidDir.out - pidDir.laterData*pidDir.Kd;

        // if(abs(pidDir.out) >100) {
        //     if(pidDir.out > 0 ) {
        //         pidDir.out = 100;
        //     }else{
        //         pidDir.out = -100;
        //     }
        // }

        // if(pidDir.out > 40 && -pidDir.currentData > 0) {
        //     pidDir.out = 40;
        // }else if(pidDir.out < -40 && -pidDir.currentData < 0){
        //     pidDir.out = -40;
        // }

        // if(degBetween(pidDir.target,pidDir.rawData) < 2) {
        //     pidDir.turnDir = 0;
        // }else{
        //     pidDir.turnDir = pidDir.out;
        // }
        // pidDir.lastData = pidDir.currentData;
    }
}

int16_t getTurnAttitude(){
    return pidDir.turnDir;
}
#endif