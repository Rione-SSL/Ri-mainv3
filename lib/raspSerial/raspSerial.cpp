#include "raspSerial.h"

raspSerial::raspSerial(PinName TX, PinName RX) : device(TX, RX) {
    device.baud(115200);                                   //通信速度最速
    device.attach(callback(this, &raspSerial::receiveRx)); //角度割り込み入力
    bufferCount = 0;
}

raspSerial::raspSerial(PinName TX, PinName RX, int baud) : device(TX, RX) {
    device.baud(baud);                                     //通信速度最速
    device.attach(callback(this, &raspSerial::receiveRx)); //角度割り込み入力
    bufferCount = 0;
}

//受信割り込み関数
void raspSerial::receiveRx() {
    bufferCount++;
    buffer[bufferCount - 1] = device.getc();
    if (buffer[0] != 0xFF) bufferCount--;
    if (bufferCount == BUFFER_SIZE) {
        // bufferCount == BUFFER_SIZE 全ての通信が完了した時に以下を実行
        if (buffer[0] == 0xFF) {
            bufferCount = 0;
            //受信バッファに溜まったデータを実用の変数に代入していく
            // for使うより直接代入の方が早い
            info.motor[0] = (int16_t)buffer[1] - 100.0; //
            info.motor[1] = (int16_t)buffer[2] - 100.0;
            info.motor[2] = (int16_t)buffer[3] - 100.0;
            info.motor[3] = (int16_t)buffer[4] - 100.0;
            info.driblePower = (float)buffer[5] / 100;
            info.kickerPower[STRAIGHT_KICKER] = (float)buffer[6] / 100;
            info.kickerPower[CHIP_KICKER] = (float)buffer[6] / 100;
            info.emergency = buffer[7];
        }
    }
}

// void raspSerial::sendToRasp(RobotInfo info) {
//     uint8_t buffer[8];
//     buffer[0] = 0xFF;
//     buffer[1] = info.volt;
//     buffer[2] = info.volt;
//     buffer[3] = info.photoSensor >> 8;     // MSB
//     buffer[4] = info.photoSensor & 0x00FF; // LSB
//     buffer[5] = info.isHoldBall;
//     buffer[6] = (int16_t)(info.imuDir) >> 8;     // MSB
//     buffer[7] = (int16_t)(info.imuDir) & 0x00FF; // LSB
//     //送信バッファに溜まったデータを送信
//     for (int i = 0; i < 8; i++) {
//         device.putc(buffer[i]);
//     }
// }

void raspSerial::sendToRasp(RobotInfo info) {
    uint8_t buffer[8];
    buffer[0] = 0xFF;
    buffer[1] = 10;
    buffer[2] = 20;
    buffer[3] = 30;
    buffer[4] = 40;
    buffer[5] = 50;
    buffer[6] = 60;
    buffer[7] = 70;
    //送信バッファに溜まったデータを送信
    for (int i = 0; i < 8; i++) {
        device.putc(buffer[i]);
    }
}

void raspSerial::put(int val) { device.putc(val); }
void raspSerial::get(float &a, int num) { a = info.motor[num]; }
void raspSerial::print(float val) { device.printf("%f\r\n", val); }
void raspSerial::syncFromRasp(RobotInfo &_info) { _info = info; }