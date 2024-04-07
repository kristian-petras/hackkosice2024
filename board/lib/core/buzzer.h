#ifndef BUZZER_H
#define BUZZER_H
#include <Arduino.h>

const int BUZZER = 3;

void init_buzzer();

void tone(uint16_t frequency, uint16_t duration);
void play(uint16_t* frequencies, uint16_t* durations, uint16_t size, uint32_t unitNoteDuration);

#endif // BUZZER_H