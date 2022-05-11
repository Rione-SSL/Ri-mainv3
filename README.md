# Ri-mainv3


## 動作環境

- PlatformIO
- mbed OS 5(framework-mbed@~5.51203.190509)
- Nucleo F303K8T6

## 環境構築

### Requirements

- python3.9.11
- [pyenv](https://www.karakaram.com/mac-pyenv-install/)
- [VSCode](https://azure.microsoft.com/ja-jp/products/visual-studio-code/)
- [PlatformIO](https://www.google.com/search?client=safari&rls=en&q=PlatformIO&ie=UTF-8&oe=UTF-8)

## VSCodeにPlatformIOの環境構築をする動画

- **Mac,Ubuntuの人はpyenvでPython3.9.11あたりをインストールし、globalにしてから環境構築を始めてください(ここだけちょっと特殊)**
- Windows用ですが、VSCodeにPlatformIOをインストールするところはMacも同様です。

[https://www.youtube.com/watch?v=ERTaB7_YpOk&feature=youtu.be](https://www.youtube.com/watch?v=ERTaB7_YpOk&feature=youtu.be)

## PlatformIOをmbed OS5に対応させる

- デフォルトではmbed OS6を使うようになっています。以下の記事の手順を踏まないとビルド時にpython系統のエラーを出します(バグ)
- 後々プログラムを実行する時に以下リンク先の処理が必要になりますので、覚えておいてください。

[PlatformIOでmbedOS6ではなくOS5で開発する方法 - Qiita](https://qiita.com/TomiXRM/items/4478dc63301c9919cfc2)


## ファイル構造について

```
├── LICENSE
├── README.md
├── include
│   └── README
├── lib
│   ├── LGIMU             ← IMUのライブラリ
│   │   ├── LGIMU.cpp
│   │   └── LGIMU.h
│   ├── Drive              ← モーター駆動プログラム
│   │   ├── Motor.cpp
│   │   └── Motor.h
│   ├── LGkicker           ← キッカー駆動プログラム
│   │   ├── LGKicker.cpp
│   │   └── LGKicker.h
│   ├── Servo              ← ドリブラーのESC駆動プログラム
│   │   ├── Servo.cpp
│   │   └── Servo.h
│   ├── raspSerial         ← ラズパイとの通信を司るプログラムを書くところ
│   │   ├── raspSerial.cpp 
│   │   └── raspSerial.h   
│   └── setup
│       ├── RIMode.h       ← モード管理のテンプレート
│       ├── modeRun.h      ← モード管理
│ 		  ├── RobotInfo.h    ← ロボットのセンサ情報やモータ情報を格納する変数テンプレート
│       ├── pinDefs.h      ← ペリフェラルピンのdefineファイル
│       ├── setup.h        ← 諸々のインスタンス宣言や変数宣言を行うファイル
│       └── setup_common.h ← 諸々のテンプレートを各場所
├── platformio.ini ← PlatformIOのプロジェクト設定ファイル
├── src
│   ├── main.cpp           ← mainプログラム.基本的には触らない
│   └── modes              ← ユーザが基本的に触るプログラムはここに書く
│   │   ├── **modeMain.h**     ← メインモードのプログラム
│   │   ├── **modeTest.h**     ← モードのテンプレート.複製して実行するモードを増やせる
│   │   └── **modes.h**        ← モードの管理ファイル.モード追加をする時に書き足す
└── test
    └── README
```

### modes

- 実行するモードの管理をするフォルダ
    
    <aside>
    🤔 **IMUを使っての姿勢制御のテストコードを書いて試したいけど元々入ってるプログラムを書き換えるのはなぁ...**
    
    という時に、新しくモードを追加するだけで、他の機能に干渉することなくプログラムを実装•検証できます
    
    </aside>
    
- `RIMode型`のモード情報構造体で管理する
    
    ```cpp
    // RIMode構造体
    typedef struct {
        char *modeName;   　　　　　　　　// モードの名前
        char modeLetter;  　　　　　　　　// モードの文字(パソコンとのやり取りで使用します)
        mbed::Callback<void()> before; // モード実行前に1度だけ実行される関数を保持
        mbed::Callback<void()> body;   // モードのメインループ関数を保持
        mbed::Callback<void()> after;  // モード終了直後に1度だけ実行される関数を保持
    } RIMode;
    ```
    

#### モードの追加と実行

##### 1. modesディレクトリにモードファイルを追加する

(例:`modeABC.h`を生成する)

```cpp
// modeABC.h
#ifndef _MODE_ABC_ // ← インクルードガードの名前をちゃんとつけましょう
#define _MODE_ABC_ // ← インクルードガードの名前をちゃんとつけましょう

#include "setup.h"

void before_abc() {
    // bodyを実行する直前に1度だけ実行する関数
    pc.printf("before ABC\r\n");
}

void body_abc() {
    // モードのメインプログラムを書く関数.この関数がループで実行されます
    pc.printf("body ABC\r\n");
}

void after_abc() {
    // モードが切り替わり、bodyが実行し終えた直後に1度だけ実行する関数
    pc.printf("after ABC\r\n");
}

const RIMode modeABC = {
    modeName : **"mode_ABC"**, //モードの名前.コンソールで出力したりLCDに出せます.
    modeLetter : **'A'**,      //モード実行のコマンド
    before : callback(before_abc),
    body : callback(body_abc),
    after : callback(after_abc)
};

#endif
```

##### 2. `modes.h`にモードの追加を記述

```cpp
#ifndef _MODES_
#define _MODES_
// modes
#include "modeTest.h"
#include "modeMain.h"
#include **"modeABC"** //←今作ったmodeABC.hを追加

// mode registration
const int8_t **modeIndex** = **3**;//←モード数を2から3に変更
// ------------------------------------------------ ↓今作ったmodeABCを追加
const RIMode modes[modeIndex] = {modeMain, modeTest,**modeABC**};

#endif
```

##### 3. シリアルモニタ(ArduinoIDEを推奨)で`モード実行コマンド`を送信

- modeABC.hでmodeLetterに`’A’`を指定したので`A`を送信
- CR/LF(改行文字)は無しに設定してください

### raspSerialクラス

- Raspberry piとの通信は`raspSerial`クラスが使われます
- Raspberry piから受信するデータは`raspSerial::receiveRx`で編集できます

```cpp
// 受信割り込み関数
void raspSerial::receiveRx() {
    bufferCount++;
    buffer[bufferCount - 1] = device.getc();
    if (buffer[0] != 0xFF) bufferCount--;
    if (bufferCount == BUFFER_SIZE) {
        if (buffer[0] == 0xFF) {
            bufferCount = 0;
	   /* ↓↓↓↓↓↓↓↓↓↓↓受信データの受け渡し↓↓↓↓↓↓↓↓↓↓↓ */
            info.motor[0] = (float)buffer[1] - 100.0;
            info.motor[1] = (float)buffer[2] - 100.0;
            info.motor[2] = (float)buffer[3] - 100.0;
            info.motor[3] = (float)buffer[4] - 100.0;
            info.driblePower = (float)buffer[5] / 100;
            info.kickerPower = (float)buffer[6] / 100;
        }
    }
}
```

- **変数の型は`uint8_t`です。0以上の整数しか扱えません**
    - **2byte(int16_tなど)を送りたい時は上位バイトと下位バイトに分けて送信してください**
    - **キッカ・ドリブラのパワーは0~100で送ってください**
    - **モーターパワーは0~200で送ってください**
- 通信で扱うbyte数を増やすには`raspSerial.h`の`BUFFER_SIZE`を変更してください
    - 現在は7byteです
    
    | バイト数 | データ |
    | --- | --- |
    | 1バイト目 | 0xFF(最初に送る文字) |
    | 2バイト目 | モータパワー(1) |
    | 3バイト目 | モータパワー(2) |
    | 4バイト目 | モータパワー(3) |
    | 5バイト目 | モータパワー(4) |
    | 6バイト目 | ドリブラパワー |
    | 7バイト目 | キッカーパワー |

### RobotInfo

- ロボットのセンサ情報やアクチュエータの情報をまとめた構造体
- 基本的にRotovInfoの参照渡しでraspSerialクラスやMotorクラスと情報のやり取りをする
- やり取りをする情報やセンサの情報を追加したい時は`RobotInfo`の中に変数を追加してください

```cpp
typedef struct {
    float motor[4];       // モーターパワー(-100~100)
    float driblePower;    // ドリブルーパワー(0~100)
    float kickerPower;    // ドリブルーパワー(0~100)
    float batteryVoltage; // バッテリー電圧
    float photoSensor;    // ボール補足センサの値(0.0~1.0)
    bool isHoldBall;      // 
    float imuDir;
} RobotInfo;
```

### その他

#### pinDefs.h

- ペリフェラルピンの名前を決めておくファイル
- マイコンを変更した時にこのヘッダファイルをいじるだけで乗り換えが効くのでこうしています

#### modeRun.h

- modes.hで設定したモードを実行するプログラムが書かれている
- 基本的にいじらないでください
- modes.hにない文字列が送られた時の例外処理なども書いています

#### setup.h / setup_common.h

- ここにペリフェラルやクラスの宣言を書くようにしてください
- 変数の宣言は`setup.h`
- 変数の型(typedef structなど)の使い回しをするテンプレートやdefineは`setup_common.h`

#### RIMode.h

- mbed::Callback<void()>を使って関数を保持しています
- modeNameはLCDに出力したりできる予定
- modeLetterはPCからシリアル通信で実行する時に使うコマンドです
