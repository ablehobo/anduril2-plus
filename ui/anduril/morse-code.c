//#include "fsm/spaghetti-monster.h"
#include "anduril/morse-code.h"
//#include "aux-leds.h"  // Assuming this handles LED blinking
#include "misc.h"      // Assuming this includes delay functions

#define DEFAULT_MORSE_SPEED 100
static uint16_t morse_speed = DEFAULT_MORSE_SPEED;  // Speed in milliseconds

// Morse code patterns for A-Z
const char* morse_pattern[] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
    "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
    "..-", "...-", ".--", "-..-", "-.--", "--.."
};

uint8_t message[MAX_MESSAGE_LENGTH];
uint8_t message_length = 0;

void init_message() {
    message[0] = 'A';
    message[1] = 'B';
    message[2] = 'C';
    message_length = 3;
}

#define INVALID_MORSE_CODE 255

enum MorseCode map_button_to_morse(uint8_t presses) {
    if (presses >= 1 && presses <= 26) {
        return (enum MorseCode)presses;
    } else {
        return INVALID_MORSE_CODE; // Invalid input
    }
}

// Store the mapped Morse code character
void store_morse_code_input(uint8_t presses) {
    if (message_length < MAX_MESSAGE_LENGTH) {
        enum MorseCode letter = map_button_to_morse(presses);
        if (letter != INVALID_MORSE_CODE) {
            message[message_length++] = letter;
        }
    }
}

// Blink a short duration (dot)
void blink_short(uint8_t level) {
    set_level(level);
    nice_delay_ms(morse_speed); // Adjust as needed
    set_level(0);
    nice_delay_ms(morse_speed);
}

// Blink a long duration (dash)
void blink_long(uint8_t level) {
    set_level(level);
    nice_delay_ms(3 * morse_speed); // Adjust as needed
    set_level(0);
    nice_delay_ms(morse_speed);
}

// Blink Morse code for a single letter
void blink_morse_code(enum MorseCode letter, uint8_t level) {
    const char* pattern = morse_pattern[letter - 1];
    while (*pattern) {
        if (*pattern == '.') {
            blink_short(level);
        } else if (*pattern == '-') {
            blink_long(level);
        }
        pattern++;
    }
    // Delay between letters
    nice_delay_ms(3 * morse_speed);
}

// Display the entire Morse code message
void display_morse_code_message() {
    for (uint8_t i = 0; i < message_length; i++) {
        blink_morse_code((enum MorseCode)message[i], DEFAULT_MORSE_SPEED);
    }
}

// Function to set Morse code speed
void set_morse_speed(uint16_t speed) {
    morse_speed = speed;
}
