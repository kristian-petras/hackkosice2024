#include <Arduino.h>
#include <DebounceEvent.h>


const int LED_4 = 13;
const int _D1_INVERTED = 13;
const int _D2_INVERTED = 12;
const int _D3_INVERTED = 11;
const int _D4_INVERTED = 10;

const int BUTTON_1 = A1;
const int BUTTON_2 = A2;
const int BUTTON_3 = A3;

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
