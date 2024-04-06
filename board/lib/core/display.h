#ifndef DISPLAY_H
#define DISPLAY_H

#include <ShiftDisplay2.h>

const bool _SWAP_SHIFT_REGISTERS = true;
const int _DISPLAY_SIZE = 4;

const int _DISPLAY_LATCH = 4;
const int _DISPLAY_CLOCK = 7;
const int _DISPLAY_DATA = 8;

ShiftDisplay2 get_display();

#endif // DISPLAY_H