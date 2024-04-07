#ifndef STREAM_H
#define STREAM_H

#include <Arduino.h>

void read_data(uint16_t* frequencies, uint16_t* durations, uint16_t index, uint16_t count);
uint32_t read_command();
bool check_command();

#endif // STREAM_H