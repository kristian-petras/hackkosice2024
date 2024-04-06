#include <display.h>

const bool SWAP_SHIFT_REGISTERS = true;
const int DISPLAY_SIZE = 4;

const int DISPLAY_LATCH = 4;
const int DISPLAY_CLOCK = 7;
const int DISPLAY_DATA = 8;

ShiftDisplay2 Display::get_default() {
    ShiftDisplay2 display(
        DISPLAY_LATCH, DISPLAY_CLOCK, DISPLAY_DATA,
        COMMON_ANODE, DISPLAY_SIZE, SWAP_SHIFT_REGISTERS);

    return display;
}

