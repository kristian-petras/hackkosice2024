#include <Arduino.h>
#include <DebounceEvent.h>
#include <display.h>
#include "constants.h"

DebounceEvent* button;
ShiftDisplay2 display = Display::get_default();
#define BLOCK_SIZE 4 // Define the size of each block

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

void read_blocks_data(){
  if (Serial.available() >= 4) {
    uint16_t commandType = Serial.read() | (Serial.read() << 8);
    uint16_t numBlocks = 0; // Used only for specific commands
    
    // Command to process a specific number of blocks
    if (commandType == 3) {
      numBlocks = Serial.read() | (Serial.read() << 8);
      for (uint16_t i = 0; i < numBlocks && Serial.available() >= 4; i++) {
        uint32_t block = Serial.read()
                         | (Serial.read() << 8)
                         | (Serial.read() << 16)
                         | (Serial.read() << 24);
        // Process the block here
        Serial.print("Received block: ");
        Serial.println(block, HEX);
      }
    } 
    // New command to read all available data
    else if (commandType == 4) {
      while (Serial.available() > 0) {
        // Read and process all available data
        char data = Serial.read();
        Serial.print("Received data: ");
        Serial.println(data, HEX);
      }
    }
    // Add delays or synchronization as needed
  }

  
}

void setup() {
    Serial.begin(115200); 
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
    read_blocks_data();
}
