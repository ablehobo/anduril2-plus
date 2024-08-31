// morse_code.h: Morse code definitions and functions
#ifndef MORSE_CODE_H
#define MORSE_CODE_H

#include <stdint.h>

// Enumerator for Morse code letters
enum MorseCode {
    A = 1, B, C, D, E, F, G, H, I, J,
    K, L, M, N, O, P, Q, R, S, T,
    U, V, W, X, Y, Z
};

// Maximum message length
#define MAX_MESSAGE_LENGTH 100

// Function prototypes
enum MorseCode map_button_to_morse(uint8_t presses);
void store_morse_code_input(uint8_t presses);
void display_morse_code_message();
void set_morse_speed(uint16_t speed);  // Function to set the Morse code speed
void init_message();                   // Function to initialize the message

// External variables
extern uint8_t message[MAX_MESSAGE_LENGTH];
extern uint8_t message_length;

#endif // MORSE_CODE_H
