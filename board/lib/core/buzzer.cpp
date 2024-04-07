#include <buzzer.h>
#include <Arduino.h>

void init_buzzer() {
    pinMode(BUZZER, OUTPUT);
}

void tone(int frequency, int duration) {
    tone(BUZZER, frequency, duration);
}

void play(int *frequencies, int pause, int size) {
    for (int i = 0; i < size; i++) {
        tone(frequencies[i], pause);
        delay(pause);
    }
}
