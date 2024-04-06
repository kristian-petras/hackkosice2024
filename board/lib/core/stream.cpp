#include <Arduino.h>

u_int16_t read_command() {
    return 0;
}

void read_data(uint16_t* buffer, size_t size) {
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