// Raspberry Pi Pico 2 Pin Configuration
//
// INPUT                          |   OUTPUT
// -------------------------------|--------------------------------------
// SW1 ----------------> GPIO5 ---|-- GPIO8 ------> Signal1 ----- 700Hz
// SW2 ----------------> GPIO4 ---|-- GPIO9 ------> Signal2 ----- 750Hz
// SW3 ----------------> GPIO3 ---|-- GPIO10 -----> Signal3 ----- 800Hz
// SW4 ----------------> GPIO2 ---|-- GPIO11 -----> Signal4 ----- 850Hz
// LEFT STICK SW ------> GPIO21 --|-- GPIO12 -----> Signal5 ----- 900Hz
// RIGHT STICK SW -----> GPIO22 --|-- GPIO13 -----> Signal6 ----- 950Hz
// LEFT STICK X -------> ADC0 ----|-- None -------- None
// LEFT STICK Y -------> ADC1 ----|-- GPIO14 -----> Signal7 ----- 1010-1090Hz
// RIGHT STICK Y ------> ADC2 ----|-- GPIO15 -----> Signal8 ----- 1110-1190Hz
// -------------------------------|--------------------------------------



#include <Arduino.h>

#define TONE_USE_INT
#define TONE_PITCH 440
#include <TonePitch.h>

// ボタンスイッチ
#define PIN_SW1 5
#define PIN_SW2 4
#define PIN_SW3 3
#define PIN_SW4 2

// スティックのボタンスイッチ
#define PIN_L_ST_SW 21
#define PIN_R_ST_SW 22

// スティックのXY
#define PIN_L_ST_X A0
#define PIN_L_ST_Y A1
#define PIN_R_ST_Y A2

// 矩形波信号出力
#define PIN_SIGNAL1 8
#define PIN_SIGNAL2 9
#define PIN_SIGNAL3 10
#define PIN_SIGNAL4 11
#define PIN_SIGNAL5 12
#define PIN_SIGNAL6 13
#define PIN_SIGNAL7 14
#define PIN_SIGNAL8 15

// 信号の基本周波数
#define FREQ_SIGNAL1 700
#define FREQ_SIGNAL2 750
#define FREQ_SIGNAL3 800
#define FREQ_SIGNAL4 850
#define FREQ_SIGNAL5 900
#define FREQ_SIGNAL6 950
#define FREQ_SIGNAL7 1050
#define FREQ_SIGNAL8 1150

#define FREQ_STEP 10

int oldSw1State = 0;
int oldSw2State = 0;
int oldSw3State = 0;
int oldSw4State = 0;
int oldLeftStickSwState = 0;
int oldRightStickSwState = 0;
int oldMappedLeftStickXValue = 0;
int oldMappedLeftStickYValue = 0;
int oldMappedRightStickYValue = 0;


void setup() {
  Serial.begin(9600);
  
  // 入力ピン
  pinMode(PIN_SW1, INPUT);      // digital
  pinMode(PIN_SW2, INPUT);      // digital
  pinMode(PIN_SW3, INPUT);      // digital
  pinMode(PIN_SW4, INPUT);      // digital
  pinMode(PIN_L_ST_SW, INPUT);  // digital
  pinMode(PIN_R_ST_SW, INPUT);  // digital
  pinMode(PIN_L_ST_X, INPUT);   // analog
  pinMode(PIN_L_ST_Y, INPUT);   // analog
  pinMode(PIN_R_ST_Y, INPUT);   // analog

  // 出力ピン
  pinMode(LED_BUILTIN, OUTPUT); // ボード上のLED

  pinMode(PIN_SIGNAL1, OUTPUT);  // SW1
  pinMode(PIN_SIGNAL2, OUTPUT);  // SW2
  pinMode(PIN_SIGNAL3, OUTPUT);  // SW3
  pinMode(PIN_SIGNAL4, OUTPUT);  // SW4
  pinMode(PIN_SIGNAL5, OUTPUT);  // Left Stick SW
  pinMode(PIN_SIGNAL6, OUTPUT);  // Right Stick SW
  pinMode(PIN_SIGNAL7, OUTPUT);  // Left Stick Y
  pinMode(PIN_SIGNAL8, OUTPUT);  // Right Stick Y

  tone(PIN_SIGNAL7, FREQ_SIGNAL7);
  tone(PIN_SIGNAL8, FREQ_SIGNAL8);

}

void loop() {

  // ボタンスイッチの値を読み取り
  int sw1State = digitalRead(PIN_SW1);
  int sw2State = digitalRead(PIN_SW2);
  int sw3State = digitalRead(PIN_SW3);
  int sw4State = digitalRead(PIN_SW4);
  int leftStickSwState = digitalRead(PIN_L_ST_SW);
  int rightStickSwState = digitalRead(PIN_R_ST_SW);

  // スティックの値の読み取り
  int leftStickXValue = analogRead(PIN_L_ST_X);
  int leftStickYValue = analogRead(PIN_L_ST_Y);
  int rightStickYValue = analogRead(PIN_R_ST_Y);

  // スティックの値をマップ -4から+4にマップ
  int mappedLeftStickXValue = map(leftStickXValue, 0, 1023, -4, 4);
  int mappedLeftStickYValue = map(leftStickYValue, 0, 1023, -4, 4);
  int mappedRightStickYValue = map(rightStickYValue, 0, 1023, -4, 4);

  // SW1/Signal1の信号制御
  if (sw1State != oldSw1State) {
    if (sw1State == 1) {
      tone(PIN_SIGNAL1, FREQ_SIGNAL1);
    } else if (sw1State == 0) {
      noTone(PIN_SIGNAL1);
    }
  }

  // SW2/Signal2の信号制御
  if (sw2State != oldSw2State) {
    if (sw2State == 1) {
      tone(PIN_SIGNAL2, FREQ_SIGNAL2);
    } else if (sw2State == 0) {
      noTone(PIN_SIGNAL2);
    }
  }

  // SW3/Signal3の信号制御
  if (sw3State != oldSw3State) {
    if (sw3State == 1) {
      tone(PIN_SIGNAL3, FREQ_SIGNAL3);
    } else if (sw3State == 0) {
      noTone(PIN_SIGNAL3);
    }
  }

  // SW4/Signal4の信号制御
  if (sw4State != oldSw4State) {
    if (sw4State == 1) {
      tone(PIN_SIGNAL4, FREQ_SIGNAL4);
    } else if (sw4State == 0) {
      noTone(PIN_SIGNAL4);
    }
  }

  // LeftStickSW/Signal5の信号制御
  if (leftStickSwState != oldLeftStickSwState) {
    if (leftStickSwState == 1) {
      tone(PIN_SIGNAL5, FREQ_SIGNAL5);
    } else if (leftStickSwState == 0) {
      noTone(PIN_SIGNAL5);
    }
  }

  // RightStickSW/Signal6の信号制御
  if (rightStickSwState != oldRightStickSwState) {
    if (rightStickSwState == 1) {
      tone(PIN_SIGNAL6, FREQ_SIGNAL6);
    } else if (rightStickSwState == 0) {
      noTone(PIN_SIGNAL6);
    }
  }

  // LeftStickYValue/Signal7の信号制御
  if (mappedLeftStickYValue != oldMappedLeftStickYValue){
    int f = FREQ_SIGNAL7 + mappedLeftStickYValue * FREQ_STEP;
    tone(PIN_SIGNAL7, f);
  }

  // RightStickYValue/Signal8の信号制御
  if (mappedRightStickYValue != oldMappedRightStickYValue){
    int f = FREQ_SIGNAL8 + mappedRightStickYValue * FREQ_STEP;
    tone(PIN_SIGNAL8, f);
  }




  Serial.print(sw1State);
  Serial.print("\t");
  Serial.print(sw2State);
  Serial.print("\t");
  Serial.print(sw3State);
  Serial.print("\t");
  Serial.print(sw4State);
  Serial.print("\t");
  Serial.print(leftStickSwState);
  Serial.print("\t");
  Serial.print(rightStickSwState);
  Serial.print("\t");
  Serial.print(leftStickXValue);
  Serial.print("\t");
  Serial.print(mappedLeftStickXValue);
  Serial.print("\t");
  Serial.print(leftStickYValue);
  Serial.print("\t");
  Serial.print(mappedLeftStickYValue);
  Serial.print("\t");
  Serial.print(rightStickYValue);
  Serial.print("\t");
  Serial.println(mappedRightStickYValue);

  // 古いデータを保持
  oldSw1State = sw1State;
  oldSw2State = sw2State;
  oldSw3State = sw3State;
  oldSw4State = sw4State;

  oldLeftStickSwState = leftStickSwState;
  oldRightStickSwState = rightStickSwState;

  oldMappedLeftStickXValue = mappedLeftStickXValue;
  oldMappedLeftStickYValue = mappedLeftStickYValue;
  oldMappedRightStickYValue = mappedRightStickYValue;

  // デバッグ用：オンボードLED
  digitalWrite(LED_BUILTIN, rightStickSwState);

  delay(10);  // wait for a second


}
