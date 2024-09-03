#include "morse-code.h"
#include "misc.h"  // Assuming this includes delay functions
#include <stdint.h>

// Define the morse_speed variable
uint8_t morse_speed = DEFAULT_MORSE_SPEED;  // Speed in milliseconds
uint8_t message_length = INVALID_MORSE_CODE; // Default to invalid message so init runs

typedef struct {
    uint8_t sequence[4];  // Max length of Morse code is 4 elements
    uint8_t length;       // Number of elements in the sequence
} PreProcessedMorseCode;

static const PreProcessedMorseCode morse_code_sequences[] = {
    {{1, 3}, 2},  // A: ".-"
    {{3, 1, 1, 1}, 4},  // B: "-..."
    {{3, 1, 3, 1}, 4},  // C: "-.-."
    {{3, 1, 1}, 3},  // D: "-.."
    {{1}, 1},  // E: "."
    {{1, 1, 3, 1}, 4},  // F: "..-."
    {{3, 3, 1}, 3},  // G: "--."
    {{1, 1, 1, 1}, 4},  // H: "...."
    {{1, 1}, 2},  // I: ".."
    {{1, 3, 3, 3}, 4},  // J: ".---"
    {{3, 1, 3}, 3},  // K: "-.-"
    {{1, 3, 1, 1}, 4},  // L: ".-.."
    {{3, 3}, 2},  // M: "--"
    {{3, 1}, 2},  // N: "-."
    {{3, 3, 3}, 3},  // O: "---"
    {{1, 3, 3, 1}, 4},  // P: ".--."
    {{3, 3, 1, 3}, 4},  // Q: "--.-"
    {{1, 3, 1}, 3},  // R: ".-."
    {{1, 1, 1}, 3},  // S: "..."
    {{3}, 1},  // T: "-"
    {{1, 1, 3}, 3},  // U: "..-"
    {{1, 1, 1, 3}, 4},  // V: "...-"
    {{1, 3, 3}, 3},  // W: ".--"
    {{3, 1, 1, 3}, 4},  // X: "-..-"
    {{3, 1, 3, 3}, 4},  // Y: "-.--"
    {{3, 3, 1, 1}, 4},  // Z: "--.."
    {{0}, 7}  // Space: " " (7 units for a space)
};

static void blink(uint8_t brightness, uint8_t duration) {
    set_level(brightness);
    nice_delay_ms(duration * morse_speed);
    set_level(0);
    nice_delay_ms(morse_speed);  // Inter-element gap
}

void decode_morse_pattern(uint8_t letter_index, uint8_t level) {
    PreProcessedMorseCode code = morse_code_sequences[letter_index];

    if (letter_index == 26) {  // Assuming space is mapped to index 26
        // Handle space: 7 * morse_speed for a space
        nice_delay_ms(7 * morse_speed);
    } else {
        for (int i = 0; i < code.length; i++) {
            if (code.sequence[i] == 3) {
                blink(level, 3);  // Dash
            } else if (code.sequence[i] == 1) {
                blink(level, 1.5);  // Dot
            }

            set_level(0);
            nice_delay_ms(morse_speed);  // Inter-element gap
        }

        nice_delay_ms(3 * morse_speed);  // Final delay between letters
    }
}

uint8_t message[MAX_MESSAGE_LENGTH];

void init_message(void) {
    message[0] = 14; // A
    message[1] = 15; // B
    message[2] = 20; // C
    message_length = 3;
}

MorseCode map_button_to_morse(uint8_t presses) {
    if (presses >= 1 && presses <= 26) {
        return presses - 1;  // Mapping 1 to A, 2 to B, etc.
    } else if (presses == 30) { // Space (mapped to 30)
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
            save_config();
        } else if (step == 2) {
            message_length = message_length > 0 ? message_length - 1 : 0;
        } else if (step == 3) {
            message_length = 0;
            save_config();
        } else if (step == 4) {
            set_morse_speed(value * 20);
            save_config();
        }
    }
}
