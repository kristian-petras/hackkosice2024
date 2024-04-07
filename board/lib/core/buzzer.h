#ifndef BUZZER_H
#define BUZZER_H

const int BUZZER = 3;

void init_buzzer();

<<<<<<< HEAD
void tone(int frequency, int duration);

void play(int frequencies[], int pause, int size);
=======
void tone(uint16_t frequency, uint16_t duration);
void play(uint16_t* frequencies, u_int16_t* durations, size_t size);
>>>>>>> 9bfdf0a (remade play)

#endif // BUZZER_H