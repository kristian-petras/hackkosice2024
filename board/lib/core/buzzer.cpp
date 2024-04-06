#include <buzzer.h>
#include <Arduino.h>

void init_buzzer() {
    pinMode(BUZZER, OUTPUT);
}

void tone(int frequency, int duration) {
    tone(BUZZER, frequency, duration);
}

void play(int frequencies[], int pause) {
    int frequencies_count = sizeof(frequencies) / sizeof(int);
    for (int i = 0; i < frequencies_count; i++) {
        tone(frequencies[i], pause);
        delay(pause);
    }
}
