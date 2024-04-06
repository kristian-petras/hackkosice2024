#include <buzzer.h>
#include <Arduino.h>

void init_buzzer() {
    pinMode(BUZZER, OUTPUT);
}

void tone(int frequency, int duration) {
    tone(BUZZER, frequency, duration);
}