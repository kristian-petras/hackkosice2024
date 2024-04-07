#ifndef STREAM_H
#define STREAM_H

#include <Arduino.h>

void read_data(uint16_t* frequencies, uint16_t* durations, uint16_t index, uint16_t count);

// Make sure that Invalid is always the last entry in the enum, without any holes
enum CommandType {
    FreqsFromSerial = 0,
    TextToSpeech = 1,
    Invalid = 2,
};

struct Command {
    CommandType type;
    uint32_t unitNoteDuration; // in milliseconds
    uint32_t payloadSize;
};

Command read_command();
bool check_command();

#endif // STREAM_H