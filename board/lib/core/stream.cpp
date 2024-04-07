#include <stream.h>

// CommandType (1byte) + Unit Note Length (1byte) + Payload size (4bytes)
#define COMMAND_SIZE_BYTES 7

// NOTE: always call check_command() before this, so it doesn't block
Command read_command() {
    Command result;
    result.type = Invalid;

    while (Serial.available() < 1) {}
    uint32_t type = Serial.read();
    if (type >= CommandType::Invalid) {
        return result;
    }
    result.type = (CommandType)type;

    while (Serial.available() < 2) {}
    uint32_t unitNoteHigh = Serial.read();
    uint32_t unitNoteLow = Serial.read();
    result.unitNoteDuration = unitNoteLow | (unitNoteHigh << 8);

    while (Serial.available() < 4) {}
    uint32_t first = Serial.read();
    uint32_t second = Serial.read();
    uint32_t third = Serial.read();
    uint32_t fourth = Serial.read();
    uint32_t payloadSize = fourth | (third << 8) | (second << 16) | (first << 24);
    result.payloadSize = payloadSize;

    return result;
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
    return Serial.available() >= COMMAND_SIZE_BYTES;
}