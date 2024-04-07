#ifndef BUZZER_H
#define BUZZER_H

const int BUZZER = 3;

void init_buzzer();

void tone(uint16_t frequency, uint16_t duration);
void play(uint16_t* frequencies, u_int16_t* durations, size_t size);

#endif // BUZZER_H