#include <stream.h>

uint32_t read_command() {
    while (true)
    {
        if (Serial.available() >= 4) {
            uint32_t first = Serial.read();
            uint32_t second = Serial.read();
            uint32_t third = Serial.read();
            uint32_t fourth = Serial.read();
            uint32_t result = fourth | (third << 8) | (second << 16) | (first << 24);
            return result;
        }
    }

    return 0;
}

void read_data(uint16_t* frequencies, uint16_t* durations, uint16_t index, uint16_t count) {
    while (true)
    {
        if (Serial.available() >= count) {
            uint32_t first_frequency = Serial.read();
            uint32_t second_frequency = Serial.read();
            uint32_t first_duration = Serial.read();
            uint32_t second_duration = Serial.read();
            frequencies[index] = second_frequency | (first_frequency << 8);
            durations[index] = second_duration | (first_duration << 8);
            return;
        }
    }

}

/* void read_data(uint16_t* buffer, size_t size) {
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
} */