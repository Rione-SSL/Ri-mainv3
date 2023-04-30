#pragma once

#include <mbed.h>

// parameters
#define BAUDLATE 230400

// pinNames
#define CAN_TX PA_11
#define CAN_RX PA_12
#define MOTOR_TEST_SW A0

#define BALL_PHOTOSENS A6
#define RASPI_SIG D11
#define LED1 D3
#define VOLT_IN PA_0

#define KICKER_STRAIGHT PA_8
#define KICKER_CHIP PB_4
#define DRIB_PWM D6

#define TEST_DRIB D7
#define TEST_KICK D8

#define RASP_TX D1
#define RASP_RX D0

// State definition
#define STRAIGHT_KICKER 0
#define CHIP_KICKER 1
#define MODE_UNMATCH -1
#define IMU_CALIBURATION_2 2 // 何これ
#define IMU_CALIBURATION_3 3 // 何これ
#define IMU_CALIBURATION info.imuStatus == IMU_CALIBURATION_2 || info.imuStatus == IMU_CALIBURATION_3

typedef struct {
    int16_t motor[4];
    // モータの速度,なぜかMDが2byte受信なのでint16_tにしている
    float driblePower;
    // ドリブルの強さ(速さ),getするデータはuint8_tだが、ハードウェアAPIが　floatになっているのでfloat型
    float kickerPower[2];
    // キッカーの強さ,getするデータはuint8_tだが、ハードウェアAPIが　floatになっているのでfloat型
    volatile uint8_t volt;
    // バッテリー電圧
    uint16_t photoSensor;
    // フォトセンサの1000分率
    bool isHoldBall;
    // ボールを持っているか
    float imuDir;
    float imuDirPrev;
    // PID制御するためにfloat型である必要がある。
    float imuTargetDir;
    // PID制御するためにfloat型である必要がある。
    bool emergency;
    // 危険信号。ロボットに止まって欲しい時にtrueにする
    uint8_t imuStatus;
    // 0:正の角度 1:負の角度 2:IMU0度設定
} RobotInfo;

extern RobotInfo info;