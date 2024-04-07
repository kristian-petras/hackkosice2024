#ifndef STREAM_H
#define STREAM_H

u_int16_t read_command();
void read_data(uint16_t* frequencies, u_int16_t* durations, size_t size);

#endif // STREAM_H