#include <Arduino.h>
#include <display.h>
#include <led.h>
#include <button.h>
#include <buzzer.h>
#include <stream.h>

#include <Talkie.h>
#include <Vocab_Special.h>
#include <Vocab_US_Acorn.h>

#define BUFFER_SIZE 1024 * 4
#define MESSAGE_SIZE 4
#define SEGMENT_COUNT 4
#define DEFAULT_CHARACTER 26

#define SAY_CHARACTER(expression) \
    switch (expression) { \
    case 'A': voice.sayQ(spa_A); break; \
    case 'B': voice.sayQ(spa_B); break; \
    case 'C': voice.sayQ(spa_C); break; \
    case 'D': voice.sayQ(spa_D); break; \
    case 'E': voice.sayQ(spa_E); break; \
    case 'F': voice.sayQ(spa_F); break; \
    case 'G': voice.sayQ(spa_G); break; \
    case 'H': voice.sayQ(spa_H); break; \
    case 'I': voice.sayQ(spa_I); break; \
    case 'J': voice.sayQ(spa_J); break; \
    case 'K': voice.sayQ(spa_K); break; \
    case 'L': voice.sayQ(spa_L); break; \
    case 'M': voice.sayQ(spa_M); break; \
    case 'N': voice.sayQ(spa_N); break; \
    case 'O': voice.sayQ(spa_O); break; \
    case 'P': voice.sayQ(spa_P); break; \
    case 'Q': voice.sayQ(spa_Q); break; \
    case 'R': voice.sayQ(spa_R); break; \
    case 'S': voice.sayQ(spa_S); break; \
    case 'T': voice.sayQ(spa_T); break; \
    case 'U': voice.sayQ(spa_U); break; \
    case 'V': voice.sayQ(spa_V); break; \
    case 'W': voice.sayQ(spa_W); break; \
    case 'X': voice.sayQ(spa_X); break; \
    case 'Y': voice.sayQ(spa_Y); break; \
    case 'Z': voice.sayQ(spa_Z); break; \
    case ' ': voice.sayQ(spa_ESCAPE); break; \
    default: Serial.println("Character not supported."); break; \
    }

Talkie voice(true, false);
ShiftDisplay2 display = get_display();

void setup() {
    Serial.begin(115200);
    Serial.println("Startup");
    init_led();
    init_button();
    init_buzzer();
}

uint16_t frequencies[BUFFER_SIZE];
uint16_t durations[BUFFER_SIZE];

DebounceEvent* button_1 = get_button(0);
DebounceEvent* button_2 = get_button(1);
DebounceEvent* button_3 = get_button(2);

char display_data[SEGMENT_COUNT + 1] = { ' ', ' ', ' ', ' ', '\0' };
int selected_character_index = 0;

void play_sound(uint16_t unitNoteDuration, uint16_t size) {
    Serial.printf("Playing sound with delay %d and size %d\n", unitNoteDuration, size);

    for (int i = 0; i < size; i++) {
        read_data(frequencies, durations, i, MESSAGE_SIZE);
        Serial.printf("Received data (%d/%d):(%d - %d)\n", i + 1, size, frequencies[i], durations[i]);

        float percentage = (i + 1) * 100 / size;
        int ledsToTurnOn = percentage / 20;

        for (int j = 0; j < 4; j++) {
            if (j < ledsToTurnOn) {
                led_toggle(j, LOW);
            }
            else {
                led_toggle(j, HIGH);
            }
        }
    }

    play(frequencies, durations, size, unitNoteDuration);
}

char get_character(int value) {
    if (value >= 0 && value <= 25) {
        return 'A' + value;
    }
    else if (value == 26) {
        return ' ';
    }
    else {
        return '-'; // Invalid value
    }
}

char to_uppercase(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 'A';
    }
    else {
        return c;
    }
}

int selected_character = DEFAULT_CHARACTER;

int cycle_counter(bool increment, int counter, int start, int end) {
    int c = counter;
    if (increment) {
        c++;
        if (c > end) {
            c = start;
        }
    }
    else {
        c--;
        if (c < start) {
            c = end;
        }
    }
    return c;
}

void loop() {
    if (check_command()) {
        Command command = read_command();
        switch (command.type) {
        case CommandType::FreqsFromSerial:
            play_sound(command.unitNoteDuration, command.payloadSize);
            break;
        case CommandType::TextToSpeech:
            for (int i = 0; i < command.payloadSize; i++) {
                char character = Serial.read();
                SAY_CHARACTER(to_uppercase(character));
            }
            break;
        }
    }
    else {
        if (is_button_pressed(button_1)) {
            selected_character = cycle_counter(false, selected_character, 0, 26);
            display_data[selected_character_index] = get_character(selected_character);
        }
        else if (is_button_pressed(button_2)) {
            selected_character = cycle_counter(true, selected_character, 0, 26);
            display_data[selected_character_index] = get_character(selected_character);
        }
        else if (is_button_pressed(button_3)) {
            // if last character, say it and reset
            if (selected_character_index == SEGMENT_COUNT - 1) {
                display.show(1000);
                for (int i = 0; i < SEGMENT_COUNT; i++) {
                    SAY_CHARACTER(display_data[i]);
                    display_data[i] = ' ';
                    display.set(display_data);
                    display.show(1000);
                }
            }
            // cycle index to next character
            selected_character_index = (selected_character_index + 1) % SEGMENT_COUNT;
            selected_character = DEFAULT_CHARACTER;
        }
        display.set(display_data);
        display.show();
    }
}

