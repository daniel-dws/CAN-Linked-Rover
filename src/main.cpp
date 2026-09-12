#include <Arduino.h>

#define LED_PIN 2

// // put function declarations here:
// int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("ESP32 blink starting");
}

void loop() {
  // put your main code here, to run repeatedly:
  static uint32_t n = 0;
  Serial.printf("blink %lu\n", n++);
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  delay(500);
}

// put function definitions here:
// int myFunction(int x, int y) {
//   return x + y;
// }