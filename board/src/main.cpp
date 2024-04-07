#include <Arduino.h>
#include <display.h>
#include <led.h>
#include <button.h>
#include <buzzer.h>
#include <stream.h>
#include <tts.h>

#include <Talkie.h>
#include <Vocab_Special.h>
#include <Vocab_US_Acorn.h>

#define BLOCK_SIZE 4 // Define the size of each block

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

void speakLetter(char letter) {
  
}

int frequencies[] = { 492, 492, 492, 492, 500, 492, 664, 1328, 656, 656, 664, 1312, 1312, 656, 664, 742, 734, 734, 734, 781, 781, 1555, 1570, 781, 781, 781, 781, 1750, 1742, 1758, 891, 1742, 1961, 992, 1961, 1953, 992, 1953, 1953, 992, 1961, 1961, 992, 1961, 1961, 1961, 992, 1961, 992, 992, 1953, 992, 992, 1953, 992, 992, 1961, 1062, 1039, 1047, 1047, 2094, 1031, 1047, 1047, 1031, 1039, 2125, 1031, 2094, 1062, 1039, 1047, 1047, 1039, 1047, 1047, 2070, 1031, 1039, 1039, 1031, 1961, 1961, 992, 992, 1961, 992, 1953, 1953, 992, 1953, 992, 992, 992, 992, 992, 1000, 1000, 992, 984, 992, 992, 984, 1961, 1961, 992, 1961, 1750, 1742, 1758, 1742, 1742, 883, 1742, 1742, 1742, 1742, 1742, 883, 883, 1750, 1750, 1773, 1742, 1742, 883, 1734, 1734, 1742, 1742, 883, 891, 1742, 781, 781, 1555, 1570, 781, 781, 781, 781, 1750, 1742, 1758, 891, 1742, 781, 781, 1562, 781, 781, 781, 781, 773, 781, 781, 1555, 789, 742, 742, 734, 734, 742, 734, 734, 734, 734, 742, 750, 734, 734, 734, 742, 734, 734, 734, 734, 734, 734, 734, 742, 734, 734, 734, 664, 1328, 656, 656, 664, 1312, 1312, 656, 656, 1312, 664, 1312, 1312, 1320, 664, 664, 664, 664, 656, 1312, 492, 492, 492, 492, 492, 492, 664, 1320, 1312, 656, 664, 1312, 1312, 656, 742, 734, 734, 734, 781, 781, 781, 1578, 781, 781, 781, 781, 1758, 1742, 1742, 891, 1742, 1961, 1961, 992, 1961, 992, 992, 1953, 992, 1961, 1961, 992, 992, 1961, 1961, 1961, 992, 1961, 992, 1953, 1953, 992, 992, 992, 992, 992, 992, 1062, 1039, 1047, 1047, 1039, 1047, 1047, 2078, 1039, 2125, 1031, 1039, 1062, 1062, 1039, 1047, 1047, 2094, 1047, 1047, 1031, 1039, 2125, 1031, 1039, 1961, 1961, 992, 1961, 992, 992, 1953, 992, 992, 1953, 992, 992, 992, 992, 1953, 1000, 1000, 1953, 992, 992, 992, 1961, 1961, 992, 992, 1758, 1742, 1750, 883, 1742, 1742, 883, 1742, 1742, 883, 1742, 1742, 883, 1750, 1742, 1758, 1758, 1742, 1742, 1742, 1742, 1742, 1742, 1742, 1773, 1742, 1742, 781, 781, 1562, 781, 781, 781, 781, 1758, 1742, 1742, 1773, 1742, 1742, 781, 781, 1578, 781, 781, 781, 781, 781, 781, 781, 1555, 734, 742, 734, 734, 734, 734, 734, 734, 734, 734, 750, 742, 734, 734, 742, 734, 734, 742, 734, 734, 734, 734, 734, 742, 734, 734, 656, 664, 1320, 1312, 656, 1312, 1312, 1312, 664, 1312, 1312, 664, 1312, 1312, 656, 664, 664, 664 };
int d = 64;

void loop() {
    Talkie voice;
    
    display.show(1000);
    display.set("HOGI");
    delay(1000);
    display.update();
    //read_data();
    int size_freq = sizeof(frequencies) / sizeof(int);
    //play(frequencies, d, size_freq); // temporary, will make it non-blocking later
    

    //Part of code, that has emotional damage when called from any other place
    const char* message = "PETO EDO SIMON TINO";
    for(int i = 0; message[i] != '\0'; i++) {
        switch(message[i]) {
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
  }

  
}
