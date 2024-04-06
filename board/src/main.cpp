#include <Arduino.h>
#include <DebounceEvent.h>
#include <display.h>
#include "constants.h"

DebounceEvent* button;
ShiftDisplay2 display = Display::get_default();

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

void play_buzzer(int delay_ms) {
    analogWrite(3, 500);
    delay(delay_ms);
    analogWrite(3, LOW);
}

void display_demo() {
    for (int i = 3; i > 0; i--) {
        // store number and show it for 400ms
        display.set(i, ALIGN_CENTER);
        display.show(400);
        // add dot to stored number and show it for 400ms
        display.changeDot(1);
        display.show(400);
    }
    display.set("HOGI"); // store "GO"
}

void setup() {
    pinMode(_D1_INVERTED, OUTPUT);
    pinMode(_D2_INVERTED, OUTPUT);
    pinMode(_D3_INVERTED, OUTPUT);
    pinMode(_D4_INVERTED, OUTPUT);
    pinMode(BUTTON_1, INPUT_PULLUP);
    pinMode(BUZZER, OUTPUT);

    button = new DebounceEvent(BUTTON_1, BUTTON_PUSHBUTTON | BUTTON_DEFAULT_HIGH | BUTTON_SET_PULLUP, 50, 500);
    turn_off_leds();

    display_demo();
}

void loop() {
    if (unsigned int event = button->loop()) {
        if (event == EVENT_RELEASED) {
            turn_on_leds();
            play_buzzer(1000);
        }
    }

    display.update();
}
