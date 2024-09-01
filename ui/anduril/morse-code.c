#include "morse-code.h"
#include "misc.h"  // Assuming this includes delay functions
#include <stdint.h>

// Define the morse_speed variable
uint8_t morse_speed = DEFAULT_MORSE_SPEED;  // Speed in milliseconds
uint8_t message_length = INVALID_MORSE_CODE; // Default to invalid message so init runs

// Compressed Morse code patterns stored as 16-bit integers
static const uint16_t morse_pattern_compressed[] = {
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

// Lengths of each Morse code pattern
static const uint8_t morse_pattern_lengths[] = {
    4, 9, 11, 7, 1, 9, 9, 7, 3, 13,
    7, 9, 7, 5, 11, 11, 13, 7, 5, 3,
    7, 9, 7, 11, 13, 11
};

static void blink(uint8_t brightness, uint8_t duration) {
    set_level(brightness);
    nice_delay_ms(duration * morse_speed);
    set_level(0);
    nice_delay_ms(morse_speed);  // Inter-element gap
}

void decode_morse_pattern(MorseCode letter_index, uint8_t brightness) {
    uint16_t pattern = morse_pattern_compressed[letter_index];
    uint8_t length = morse_pattern_lengths[letter_index];

    for (int i = length - 1; i >= 0; i--) {
        if (letter_index == 26) {
            nice_delay_ms(6 * morse_speed);  // Inter-word gap
            return;
        } else if (pattern & (1 << i)) {  // Dash
            if (pattern & (1 << (i - 1))) {
                blink(brightness, 3); // Dash is three units
                i--;  // Skip next bit as part of dash
            } else {
                blink(brightness, 1);  // Dot is one unit
            }
        }
    }
    nice_delay_ms(3 * morse_speed);  // Inter-letter gap
}

uint8_t message[MAX_MESSAGE_LENGTH];

void init_message(void) {
    message[0] = 0; // A
    message[1] = 1; // B
    message[2] = 2; // C
    message_length = 3;
}

MorseCode map_button_to_morse(uint8_t presses) {
    if (presses >= 1 && presses <= 26) {
        return presses - 1;  // Mapping 1 to A, 2 to B, etc.
    } else if (presses == 30) { //30 here because it is easy to get to by 3x1H
        return 26;  // Space
    } else {
        return INVALID_MORSE_CODE; // Invalid input
    }
}

void store_morse_code_input(uint8_t presses) {
    if (message_length < MAX_MESSAGE_LENGTH) {
        MorseCode letter = map_button_to_morse(presses);
        if (letter != INVALID_MORSE_CODE) {
            message[message_length++] = letter;
        }
    }
}

void display_morse_code_message(uint8_t brightness) {
    for (uint8_t i = 0; i < message_length; i++) {
        decode_morse_pattern(message[i], brightness);
    }
}

void set_morse_speed(uint8_t speed) {
    morse_speed = speed;
}

void morse_config_save(uint8_t step, uint8_t value) {
    if (value) {
        if (step == 1) {
            store_morse_code_input(value);
        } else if (step == 2) {
            message_length = message_length > 0 ? message_length - 1 : 0;
        } else if (step == 3) {
            message_length = 0;
        } else if (step == 4) {
            set_morse_speed(value * 20);
        }
    }
}