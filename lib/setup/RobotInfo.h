#ifndef _ROBOT_INFO_
#define _ROBOT_INFO_

#define STRAIGHT_KICKER 0
#define CHIP_KICKER 1

typedef struct {
    int16_t motor[4];
    //モータの速度,なぜかMDが2byte受信なのでint16_tにしている
    float driblePower;
    //ドリブルの強さ(速さ),getするデータはuint8_tだが、ハードウェアAPIが　floatになっているのでfloat型
    float kickerPower[2];
    // キッカーの強さ,getするデータはuint8_tだが、ハードウェアAPIが　floatになっているのでfloat型
    volatile uint8_t volt;
    //バッテリー電圧
    uint16_t photoSensor;
    //フォトセンサの1000分率
    bool isHoldBall;
    // ボールを持っているか
    float imuDir;
    // PID制御するためにfloat型である必要がある。
    bool emergency;
    //危険信号。ロボットに止まって欲しい時にtrueにする
} RobotInfo;

#endif