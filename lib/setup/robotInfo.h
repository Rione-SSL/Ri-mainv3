#ifndef _ROBOT_INFO_
#define _ROBOT_INFO_

typedef struct {
    float motor[4];
    float driblePower;
    float kickerPower;
    float batteryVoltage;
    float photoSensor;
    bool isHoldBall;
    float imuDir;
} robotInfo;

#endif