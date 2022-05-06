#include "raspSerial.h"

raspSerial::raspSerial(PinName TX, PinName RX) : device(TX, RX) {
    device.baud(115200);                                   //通信速度最速
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
            info.motor[0] = (float)buffer[1] - 100.0;
            info.motor[1] = (float)buffer[2] - 100.0;
            info.motor[2] = (float)buffer[3] - 100.0;
            info.motor[3] = (float)buffer[4] - 100.0;
            info.driblePower = (float)buffer[5];
            info.kickerPower = (float)buffer[6];
        }
    }
}

void raspSerial::put(int val) { device.putc(val); }
void raspSerial::get(float &a, int num) { a = info.motor[num]; }
void raspSerial::print(float val) { device.printf("%f\r\n", val); }
void raspSerial::syncFromRasp(RobotInfo &_info) { _info = info; }