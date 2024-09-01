#ifndef MORSE_CODE_H
#define MORSE_CODE_H

#include <stdint.h>

#define INVALID_MORSE_CODE 255 // Invalid Morse code

// Enumerator for Morse code letters
enum MorseCode {
    A = 1, B, C, D, E, F, G, H, I, J,
    K, L, M, N, O, P, Q, R, S, T,
    U, V, W, X, Y, Z
};

// Maximum message length
#define MAX_MESSAGE_LENGTH 100

// Default Morse speed
#define DEFAULT_MORSE_SPEED 125 // Default speed in milliseconds

// Declare the morse_speed variable
extern uint8_t morse_speed;

// Function prototypes
enum MorseCode map_button_to_morse(uint8_t presses);
void store_morse_code_input(uint8_t presses);
void display_morse_code_message(uint8_t brightness);
void set_morse_speed(uint8_t speed);
void init_message(void);
void decode_morse_pattern(uint8_t letter_index, uint8_t level);
void blink(uint8_t brightness, uint16_t duration_multiplier);  // Combined blink function

// External variables
extern uint8_t message[MAX_MESSAGE_LENGTH];
extern uint8_t message_length;

#endif // MORSE_CODE_H
