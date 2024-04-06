#include <display.h>

ShiftDisplay2 get_display() {
    ShiftDisplay2 display(
        _DISPLAY_LATCH,
        _DISPLAY_CLOCK,
        _DISPLAY_DATA,
        COMMON_ANODE,
        _DISPLAY_SIZE,
        _SWAP_SHIFT_REGISTERS
    );
    return display;
}

