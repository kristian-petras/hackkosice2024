#ifndef LED_H
#define LED_H

const int _D1_INVERTED = 13;
const int _D2_INVERTED = 12;
const int _D3_INVERTED = 11;
const int _D4_INVERTED = 10;

void init_led();
void led_toggle(int led, int state);

#endif // LED_H