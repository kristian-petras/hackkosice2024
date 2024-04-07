#include <Arduino.h>
#include <display.h>
#include <led.h>
#include <button.h>
#include <buzzer.h>
#include <stream.h>

#define BUFFER_SIZE 1024

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


void setup() {
    Serial.begin(115200);
    init_led();
    init_button();
    init_buzzer();
    display_demo(display);
}

uint16_t frequencies[BUFFER_SIZE];
uint16_t durations[BUFFER_SIZE];

void loop() {
    // waiting for command
    Serial.println("Waiting for command...");
    uint32_t command = read_command();
    Serial.printf("Received command: %d\n", command);
    Serial.printf("Size of file: %d\n", command);
    read_data(frequencies, durations, command); // command contains size of file
    while (true)
    {
        play(frequencies, durations, command);
        delay(1000);
    }
}
