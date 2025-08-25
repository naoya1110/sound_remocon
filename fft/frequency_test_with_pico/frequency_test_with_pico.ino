#include <Arduino.h>
#define TONE_USE_INT 
#define TONE_PITCH 440 
#include <TonePitch.h>
#define PIN_SIG_OUT 7

int freq = 15250;      // 生成するトーンの周波数（Hz）

void setup() {
  pinMode(PIN_SIG_OUT, OUTPUT); 
  tone(PIN_SIG_OUT, freq);
}
void loop() {}