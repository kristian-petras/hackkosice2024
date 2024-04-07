#include <Arduino.h>
#include <display.h>
#include <led.h>
#include <button.h>
#include <buzzer.h>
#include <stream.h>

#include <Talkie.h>
#include <Vocab_Special.h>
#include <Vocab_US_Acorn.h>

#define BUFFER_SIZE 1024
#define MESSAGE_SIZE 4

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
    Serial.println("Startup");
    init_led();
    init_button();
    init_buzzer();
    display_demo(display);
}

uint16_t frequencies[BUFFER_SIZE];
uint16_t durations[BUFFER_SIZE];
Talkie voice;

int mode = 0;

void play_sound(uint16_t unitNoteDuration, uint16_t size) {
    Serial.printf("Playing sound with delay %d and size %d\n", unitNoteDuration, size);

    for (int i = 0; i < size; i++) {
        read_data(frequencies, durations, i, MESSAGE_SIZE);
        Serial.printf("Received data (%d/%d):(%d - %d)\n", i + 1, size, frequencies[i], durations[i]);
    }

    play(frequencies, durations, size, unitNoteDuration);
}

void loop() {
    if (check_command()) {
        Command command = read_command();
        switch (command.type) {
        case CommandType::FreqsFromSerial:
            play_sound(command.unitNoteDuration, command.payloadSize);
            break;
        case CommandType::TextToSpeech:
            break; // TODO
        }
    }
    else {

    }

    /*     // waiting for command
        Serial.println("Waiting for command...");
        uint32_t command = read_command();
        Serial.printf("Received command: %d\n", command);
        Serial.printf("Size of file: %d\n", command);

        for (int i = 0; i < command; i++) {
            Serial.printf("Received data (%d/%d):\n", i, command);
            read_data(frequencies, durations, i * MESSAGE_SIZE, MESSAGE_SIZE);
        }

        while (true)
        {
            play(frequencies, durations, command);
            delay(1000);
        }

        //Part of code, that has emotional damage when called from any other place
        const char* message = "PETO EDO SIMON TINO";
        for (int i = 0; message[i] != '\0'; i++) {
            switch (message[i]) {
            case 'A': voice.say(spa_A); break;
            case 'B': voice.say(spa_B); break;
            case 'C': voice.say(spa_C); break;
            case 'D': voice.say(spa_D); break;
            case 'E': voice.say(spa_E); break;
            case 'F': voice.say(spa_F); break;
            case 'G': voice.say(spa_G); break;
            case 'H': voice.say(spa_H); break;
            case 'I': voice.say(spa_I); break;
            case 'J': voice.say(spa_J); break;
            case 'K': voice.say(spa_K); break;
            case 'L': voice.say(spa_L); break;
            case 'M': voice.say(spa_M); break;
            case 'N': voice.say(spa_N); break;
            case 'O': voice.say(spa_O); break;
            case 'P': voice.say(spa_P); break;
            case 'Q': voice.say(spa_Q); break;
            case 'R': voice.say(spa_R); break;
            case 'S': voice.say(spa_S); break;
            case 'T': voice.say(spa_T); break;
            case 'U': voice.say(spa_U); break;
            case 'V': voice.say(spa_V); break;
            case 'W': voice.say(spa_W); break;
            case 'X': voice.say(spa_X); break;
            case 'Y': voice.say(spa_Y); break;
            case 'Z': voice.say(spa_Z); break;
            default: Serial.println("Character not supported."); break;
            }
        } */
}
