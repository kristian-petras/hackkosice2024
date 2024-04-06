#include <led.h>
#include <Arduino.h>

void led_toggle(int led, int state) {
    if (led == 0) {
        digitalWrite(_D1_INVERTED, state);
    }
    else if (led == 1) {
        digitalWrite(_D2_INVERTED, state);
    }
    else if (led == 2) {
        digitalWrite(_D3_INVERTED, state);
    }
    else if (led == 3) {
        digitalWrite(_D4_INVERTED, state);
    }
    else {
        Serial.printf("Invalid LED number %d\n", led);
    }
}

void init_led() {
    pinMode(_D1_INVERTED, OUTPUT);
    pinMode(_D2_INVERTED, OUTPUT);
    pinMode(_D3_INVERTED, OUTPUT);
    pinMode(_D4_INVERTED, OUTPUT);
    led_toggle(0, HIGH);
    led_toggle(1, HIGH);
    led_toggle(2, HIGH);
    led_toggle(3, HIGH);
}
