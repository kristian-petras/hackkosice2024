#include <Arduino.h>

const int LED_4 = 13;
const int _D1_INVERTED = 13;
const int _D2 = 12;
const int _D3_INVERTED = 11;
const int _D4_INVERTED = 10;

void blink_led(int pin, int delay_ms) {
    digitalWrite(pin, HIGH);
    delay(delay_ms);
    digitalWrite(pin, LOW);
    delay(delay_ms);
}

void setup() {
    pinMode(_D1_INVERTED, OUTPUT);
    pinMode(_D2, OUTPUT);
    pinMode(_D3_INVERTED, OUTPUT);
    pinMode(_D4_INVERTED, OUTPUT);
}

void loop() {
    blink_led(_D1_INVERTED, 1500);
    blink_led(_D2, 1000);
    blink_led(_D3_INVERTED, 500);
    blink_led(_D4_INVERTED, 250);
}