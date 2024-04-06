#include <Arduino.h>
#include <DebounceEvent.h>
#include "constants.h"

DebounceEvent* button;

void blink_led(int pin, int delay_ms) {
    digitalWrite(pin, HIGH);
    delay(delay_ms);
    digitalWrite(pin, LOW);
    delay(delay_ms);
}

void turn_off_leds() {
    digitalWrite(_D1_INVERTED, HIGH);
    digitalWrite(_D2_INVERTED, HIGH);
    digitalWrite(_D3_INVERTED, HIGH);
    digitalWrite(_D4_INVERTED, HIGH);
}

void turn_on_leds() {
    digitalWrite(_D1_INVERTED, LOW);
    digitalWrite(_D2_INVERTED, LOW);
    digitalWrite(_D3_INVERTED, LOW);
    digitalWrite(_D4_INVERTED, LOW);
}

void setup() {
    pinMode(_D1_INVERTED, OUTPUT);
    pinMode(_D2_INVERTED, OUTPUT);
    pinMode(_D3_INVERTED, OUTPUT);
    pinMode(_D4_INVERTED, OUTPUT);
    pinMode(BUTTON_1, INPUT_PULLUP);

    button = new DebounceEvent(BUTTON_1, BUTTON_PUSHBUTTON | BUTTON_DEFAULT_HIGH | BUTTON_SET_PULLUP, 50, 500);
    turn_off_leds();
}

void loop() {
    if (unsigned int event = button->loop()) {
        if (event == EVENT_RELEASED) {
            turn_on_leds();
        }
    }
}
