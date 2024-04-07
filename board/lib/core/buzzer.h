#ifndef BUZZER_H
#define BUZZER_H

const int BUZZER = 3;

void init_buzzer();

void tone(int frequency, int duration);

void play(int frequencies[], int pause, int size);

#endif // BUZZER_H