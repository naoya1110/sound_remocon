// Raspberry Pi Pico 2 Pin Configuration
// 
// Signal Output GP7
// SW GP11

#include <Arduino.h>
#include "hardware/adc.h"
// ADCの初期化後
adc_set_clkdiv(48.0f); // 分周器を48に設定（デフォルトは96で1MHz）

#define TONE_USE_INT
#define TONE_PITCH 440

#include <TonePitch.h>

#define PIN_SIG_OUT 7
#define PIN_SW 11
#define PIN_SIG_IN A0

int oldSwState = 0;
int swState = 0;
int freq = 1000;
int signalRead = 0;

unsigned long oldTime;
unsigned long nowTime;
unsigned long loopTime;

int onFlag = 0;


void setup() {
  Serial.begin(500000);

  pinMode(PIN_SW, INPUT);
  pinMode(PIN_SIG_IN, INPUT);
  pinMode(PIN_SIG_OUT, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  oldTime = micros();
}



void loop() {
  swState = digitalRead(PIN_SW);
  signalRead = analogRead(PIN_SIG_IN);

  nowTime = micros();
  loopTime = nowTime - oldTime;

  if (oldSwState == 0 && swState == 1) {
    // Serial.print("start");
    tone(PIN_SIG_OUT, freq);
    onFlag = 1;
  } else if (oldSwState == 1 && swState == 0){
    Serial.print("end");
    noTone(PIN_SIG_OUT);
    onFlag = 0;
  }

  if (onFlag == 1){
    Serial.print(loopTime);
    Serial.print("\t");
    Serial.print(swState);
    Serial.print("\t");
    Serial.println(signalRead);
    digitalWrite(LED_BUILTIN, 1);
  } else {
    digitalWrite(LED_BUILTIN, 0);
  }
  
  oldTime = nowTime;
  oldSwState = swState;

}
