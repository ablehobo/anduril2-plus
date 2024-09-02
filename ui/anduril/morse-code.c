#include "morse-code.h"
#include "misc.h"  // Assuming this includes delay functions
#include <stdint.h>

// Define the morse_speed variable
uint8_t morse_speed = DEFAULT_MORSE_SPEED;  // Speed in milliseconds
uint8_t message_length = INVALID_MORSE_CODE; // Default to invalid message so init runs

typedef struct {
    const char* pattern;
    uint8_t length;
} MorseCodePattern;

static const MorseCodePattern morse_patterns[] = {
    { ".-", 2 },    // A
    { "-...", 4 },  // B
    { "-.-.", 4 },  // C
    { "-..", 3 },   // D
    { ".", 1 },     // E
    { "..-.", 4 },  // F
    { "--.", 3 },   // G
    { "....", 4 },  // H
    { "..", 2 },    // I
    { ".---", 4 },  // J
    { "-.-", 3 },   // K
    { ".-..", 4 },  // L
    { "--", 2 },    // M
    { "-.", 2 },    // N
    { "---", 3 },   // O
    { ".--.", 4 },  // P
    { "--.-", 4 },  // Q
    { ".-.", 3 },   // R
    { "...", 3 },   // S
    { "-", 1 },     // T
    { "..-", 3 },   // U
    { "...-", 4 },  // V
    { ".--", 3 },   // W
    { "-..-", 4 },  // X
    { "-.--", 4 },  // Y
    { "--..", 4 }   // Z
};

static void blink(uint8_t brightness, uint8_t duration) {
    set_level(brightness);
    nice_delay_ms(duration * morse_speed);
    set_level(0);
    nice_delay_ms(morse_speed);  // Inter-element gap
}


void decode_morse_pattern(uint8_t letter_index, uint8_t level) {
    MorseCodePattern pattern = morse_patterns[letter_index];

    for (int i = 0; i < pattern.length; i++) {
        if (pattern.pattern[i] == '-') {
            blink(level, 3);  // Dash
        } else if (pattern.pattern[i] == '.') {
            blink(level, 1);  // Dot
        }
        
        // Insert inter-element delay only if this isn't the last element
        if (i < pattern.length - 1) {
            nice_delay_ms(morse_speed);
        }
    }

    // Delay between letters
    nice_delay_ms(3 * morse_speed);
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
        } else if (step == 2) {
            message_length = message_length > 0 ? message_length - 1 : 0;
        } else if (step == 3) {
            message_length = 0;
        } else if (step == 4) {
            set_morse_speed(value * 20);
        }
    }
}
