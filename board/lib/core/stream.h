#ifndef STREAM_H
#define STREAM_H

#include <Arduino.h>


void read_data(uint16_t* frequencies, u_int16_t* durations, u_int16_t size);

u_int16_t read_command();
#endif // STREAM_H