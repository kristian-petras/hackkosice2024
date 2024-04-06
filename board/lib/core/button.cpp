#include <button.h>

void init_button() {
    pinMode(_BUTTON_1, INPUT_PULLUP);
    pinMode(_BUTTON_2, INPUT_PULLUP);
    pinMode(_BUTTON_3, INPUT_PULLUP);
}

DebounceEvent* get_button(int button) {
    if (button == 0) {
        return new DebounceEvent(_BUTTON_1, BUTTON_PUSHBUTTON | BUTTON_DEFAULT_HIGH | BUTTON_SET_PULLUP, 50UL, 500UL);
    }
    else if (button == 1) {
        return new DebounceEvent(_BUTTON_2, BUTTON_PUSHBUTTON | BUTTON_DEFAULT_HIGH | BUTTON_SET_PULLUP, 50UL, 500UL);
    }
    else if (button == 2) {
        return new DebounceEvent(_BUTTON_3, BUTTON_PUSHBUTTON | BUTTON_DEFAULT_HIGH | BUTTON_SET_PULLUP, 50UL, 500UL);
    }
    else {
        Serial.printf("Invalid button number %d\n", button);
        return NULL;
    }
}

bool is_button_pressed(DebounceEvent* button) {
    if (unsigned int event = button->loop()) {
        if (event == EVENT_RELEASED) {
            return true;
        }
    }
    return false;
}