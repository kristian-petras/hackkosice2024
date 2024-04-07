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

bool check_command() {
    return Serial.available() >= 4;
}