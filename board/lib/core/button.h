#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>
#include <DebounceEvent.h>

const int _BUTTON_1 = A1;
const int _BUTTON_2 = A2;
const int _BUTTON_3 = A3;

void init_button();

DebounceEvent* get_button(int button);

bool is_button_pressed(DebounceEvent* button);

#endif // BUTTON_H