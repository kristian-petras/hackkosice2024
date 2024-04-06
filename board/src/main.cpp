#include <Arduino.h>
#include <display.h>
#include <led.h>
#include <button.h>
#include <buzzer.h>

#define BLOCK_SIZE 4 // Define the size of each block

ShiftDisplay2 display = get_display();

void display_demo(ShiftDisplay2 display) {
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

void read_blocks_data() {
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
    init_led();
    init_button();
    init_buzzer();
    display_demo(display);
}

void loop() {
    display.show(1000);
    display.set("HOGI");
    delay(1000);
    display.update();
    //read_blocks_data();
}
