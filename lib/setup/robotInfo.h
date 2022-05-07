#ifndef _ROBOT_INFO_
#define _ROBOT_INFO_

typedef struct {
    int16_t motor[4];
    float driblePower;
    float kickerPower;
    float batteryVoltage;
    float photoSensor;
    bool isHoldBall;
    float imuDir;
} RobotInfo;

#endif