#include <buzzer.h>
#include <Arduino.h>

void init_buzzer() {
    pinMode(BUZZER, OUTPUT);
}

void tone(uint16_t frequency, uint16_t duration) {
    tone(BUZZER, frequency, duration);
}

void play(uint16_t* frequencies, u_int16_t* durations, size_t size) {
    for (size_t i = 0; i < size; i++) {
        tone(frequencies[i], durations[i]);
        delay(durations[i]);
    }
}
