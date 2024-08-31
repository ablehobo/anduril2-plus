#include "morse-code.h"
#include "misc.h"  // Assuming this includes delay functions

// Define the morse_speed variable
uint16_t morse_speed = DEFAULT_MORSE_SPEED;  // Speed in milliseconds

// Morse code patterns for A-Z
const char* morse_pattern[] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
    "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
    "..-", "...-", ".--", "-..-", "-.--", "--.."
};

uint8_t message[MAX_MESSAGE_LENGTH];
uint8_t message_length = 254;

void init_message() {
    message[0] = A;
    message[1] = B;
    message[2] = C;
    message_length = 3;
}

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
void blink_short(uint8_t brightness) {
    set_level(brightness);
    nice_delay_ms(morse_speed); // Use the configured speed for dot duration
    set_level(0);
    nice_delay_ms(morse_speed);
}

// Blink a long duration (dash)
void blink_long(uint8_t brightness) {
    set_level(brightness);
    nice_delay_ms(3 * morse_speed); // Use the configured speed for dash duration
    set_level(0);
    nice_delay_ms(morse_speed);
}

// Blink Morse code for a single letter
void blink_morse_code(enum MorseCode letter, uint8_t brightness) {
    const char* pattern = morse_pattern[letter - 1];
    while (*pattern) {
        if (*pattern == '.') {
            blink_short(brightness);
        } else if (*pattern == '-') {
            blink_long(brightness);
        }
        pattern++;
    }
    // Delay between letters
    nice_delay_ms(3 * morse_speed);
}

// Display the entire Morse code message
void display_morse_code_message(uint8_t brightness) {
    for (uint8_t i = 0; i < message_length; i++) {
        blink_morse_code((enum MorseCode)message[i], brightness);
    }
}

// Function to set Morse code speed
void set_morse_speed(uint16_t speed) {
    morse_speed = speed;
}

void morse_config_save(uint8_t step, uint8_t value) {
    if (value) {
        // Step 1: Add Next Character
        if (step == 1) {
            store_morse_code_input(value);
        }
        // Step 2: Create New Message (Clear existing message)
        else if (step == 2) {
            message_length = 0;  // Clear the message
        }
        // Step 3: Morse Code Playback Speed
        else if (step == 3) {
            set_morse_speed(value);
        }
    }
}
