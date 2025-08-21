// Raspberry Pi Pico 2 Pin Configuration
// 
// Signal Output GP7
// SW GP11

#include <Arduino.h>

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


void setup() {
  Serial.begin(115200);

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

  Serial.print(loopTime);
  Serial.print("\t");
  Serial.print(swState);
  Serial.print("\t");
  Serial.println(signalRead);
  
  oldTime = nowTime;

}
