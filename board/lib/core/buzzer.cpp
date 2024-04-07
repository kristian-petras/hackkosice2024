#include <buzzer.h>
#include <Arduino.h>

void init_buzzer() {
    pinMode(BUZZER, OUTPUT);
}

void tone(uint16_t frequency, uint16_t duration) {
    tone(BUZZER, frequency, duration);
}

void play(uint16_t* frequencies, uint16_t* durations, uint16_t size) {
    for (size_t i = 0; i < size; i++) {
        // Serial.printf("Playing note %d for %d ms", frequencies[i], durations[i]);
        tone(frequencies[i], durations[i] * 50); // TODO: introduce unit note length
        delay(durations[i] * 50); // TODO: introduce unit note length
    }
}
