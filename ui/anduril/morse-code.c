#include "morse-code.h"
#include "misc.h"  // Assuming this includes delay functions
#include <stdint.h>

// Define the morse_speed variable
uint16_t morse_speed = DEFAULT_MORSE_SPEED;  // Speed in milliseconds

// Forward declarations
void blink_short(uint8_t brightness);
void blink_long(uint8_t brightness);

const uint16_t morse_pattern_compressed[] = {
    // Morse code patterns compressed into a single uint16_t (16 bits)
    0b1011,         // A: ".-"
    0b111010101,    // B: "-..."
    0b11101011101,  // C: "-.-."
    0b1110101,      // D: "-.."
    0b1,            // E: "."
    0b101011101,    // F: "..-."
    0b111011101,    // G: "--."
    0b1010101,      // H: "...."
    0b101,          // I: ".."
    0b1011101110111,// J: ".---"
    0b111010111,    // K: "-.-"
    0b101110101,    // L: ".-.."
    0b1110111,      // M: "--"
    0b11101,        // N: "-."
    0b11101110111,  // O: "---"
    0b10111011101,  // P: ".--."
    0b1110111010111,// Q: "--.-"
    0b1011101,      // R: ".-."
    0b10101,        // S: "..."
    0b111,          // T: "-"
    0b1010111,      // U: "..-"
    0b101010111,    // V: "...-"
    0b101110111,    // W: ".--"
    0b11101010111,  // X: "-..-"
    0b1110101110111,// Y: "-.--"
    0b11101110101   // Z: "--.."
};

const uint8_t morse_pattern_lengths[] = {
    4, 9, 11, 7, 1, 9, 9, 7, 3, 13,
    7, 9, 7, 5, 11, 11, 13, 7, 5, 3,
    7, 9, 7, 11, 13, 11
};

void decode_morse_pattern(uint8_t letter_index, uint8_t level) {
    uint16_t pattern = morse_pattern_compressed[letter_index];
    uint8_t length = morse_pattern_lengths[letter_index];

    for (int i = length - 1; i >= 0; i--) {
        if (pattern & (1 << i)) {  // If bit is set, it's a dash
            if (pattern & (1 << (i - 1))) {
                blink_long(level);
                i--;  // Skip the next bit since it was part of the dash
            } else {
                blink_short(level);  // Dot
            }
        }
        // Insert inter-element delay
        nice_delay_ms(morse_speed);
    }
    // Delay between letters
    nice_delay_ms(3 * morse_speed);
}

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

// Display the entire Morse code message
void display_morse_code_message(uint8_t brightness) {
    for (uint8_t i = 0; i < message_length; i++) {
        decode_morse_pattern(message[i] - 1, brightness);  // Use decode_morse_pattern instead
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