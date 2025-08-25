#include <Arduino.h>
#define TONE_USE_INT 
#define TONE_PITCH 440 
#include <TonePitch.h>
#define PIN_SIG_OUT 7

void setup() {
  pinMode(PIN_SIG_OUT, OUTPUT);
  Serial.begin(9600); // Start serial communication at 9600 baud
  Serial.println("Ready to receive frequency (Hz). Send a number, e.g., '500'");
  Serial.println("A tone will begin after the first valid input.");
}

void loop() {
  if (Serial.available()) {
    // Read the incoming string until a newline character is received
    String inputString = Serial.readStringUntil('\n');

    // Convert the string to an integer
    int freq = inputString.toInt();

    // Check if the conversion was successful and the number is a valid frequency
    if (freq > 0) {
      Serial.print("Setting tone frequency to: ");
      Serial.print(freq);
      Serial.println(" Hz");
      tone(PIN_SIG_OUT, freq); // Change the tone frequency
    } else {
      Serial.println("Invalid input. Please send a positive integer.");
    }
  }
}