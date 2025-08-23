// Raspberry Pi Pico 2 ピン設定
// 
// 信号出力 GP7
// スイッチ入力 GP11
// アナログ入力 A0

#include <Arduino.h>

// Toneライブラリの設定
// トーン生成に割り込みを使用
#define TONE_USE_INT 
// デフォルトピッチを設定（このコードでは動的に周波数が設定されるため必須ではありません）
#define TONE_PITCH 440 

// トーン生成に必要なライブラリをインクルード
#include <TonePitch.h>

// ピン番号を分かりやすいように定義
#define PIN_SIG_OUT 7 // トーン信号を出力するピン
#define PIN_SW 11     // スイッチの状態を読み取るピン
#define PIN_SIG_IN A0 // アナログ信号を読み取るピン

// グローバル変数の宣言
int oldSwState = 0;   // スイッチの前の状態
int swState = 0;      // スイッチの現在の状態
int freq = 1000;      // 生成するトーンの周波数（Hz）
int signalRead = 0;   // アナログ入力値

unsigned long oldTime;  // 前のループ実行時の時間
unsigned long nowTime;  // 現在の時間
unsigned long loopTime; // ループにかかった時間
unsigned long startTime; //
unsigned long elapsedTime; //

int onFlag = 0; // トーンがオン（1）かオフ（0）かを示すフラグ


void setup() {
  Serial.begin(115200); // シリアル通信を開始

  // 各ピンのモードを設定
  pinMode(PIN_SW, INPUT);       
  pinMode(PIN_SIG_IN, INPUT);   
  pinMode(PIN_SIG_OUT, OUTPUT); 
  pinMode(LED_BUILTIN, OUTPUT); 

  // --- ADCの高速化設定 ---
  // ADCクロック分周器を48に設定することで、ADCの速度を向上させます。
  // デフォルト値は96です。
  analogReadResolution(10);  // 解像度を10ビットに設定（高速化に寄与）
  // analogSetClockDivider(48); // 分周器を48に設定
  // --------------------------
  
  oldTime = micros(); // 最初のループ時間を記録
}


void loop() {
  // スイッチとアナログ信号の状態を読み取る
  swState = digitalRead(PIN_SW); 
  signalRead = analogRead(PIN_SIG_IN);

  // ループの経過時間を計算
  nowTime = micros();
  loopTime = nowTime - oldTime;

  // ボタンが押された瞬間を検出（前の状態が0で現在の状態が1）
  if (oldSwState == 0 && swState == 1) {
    // Serial.print("start");      // シリアルモニターに「start」と表示
    startTime = micros();
    tone(PIN_SIG_OUT, freq);    // トーン生成を開始
    onFlag = 1;                 // onFlagをオンに設定
  } 
  // ボタンが離された瞬間を検出（前の状態が1で現在の状態が0）
  else if (oldSwState == 1 && swState == 0){
    Serial.print("end");        // シリアルモニターに「end」と表示
    noTone(PIN_SIG_OUT);        // トーン生成を停止
    onFlag = 0;                 // onFlagをオフに設定
  }

  // onFlagがオンの場合、データをシリアル出力し、LEDを点灯
  if (onFlag == 1){
    elapsedTime = micros() - startTime;
    Serial.print(elapsedTime);       // 経過時間を表示
    Serial.print("\t");           // タブで区切る
    Serial.print(swState);        // スイッチの状態を表示
    Serial.print("\t");           // タブで区切る
    Serial.println(signalRead);   // アナログ入力値を表示し、改行
    digitalWrite(LED_BUILTIN, HIGH); // 内蔵LEDを点灯
  } 
  // onFlagがオフの場合、LEDを消灯
  else {
    digitalWrite(LED_BUILTIN, LOW); // 内蔵LEDを消灯
  }
  
  // 次のループのために時間とスイッチの状態を更新
  oldTime = nowTime;
  oldSwState = swState;
}
