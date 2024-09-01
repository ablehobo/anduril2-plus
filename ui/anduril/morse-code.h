#ifndef MORSE_CODE_H
#define MORSE_CODE_H

#include <stdint.h>

#define INVALID_MORSE_CODE 255 // Invalid Morse code
#define DEFAULT_MORSE_SPEED 125 // Default speed in milliseconds
#define MAX_MESSAGE_LENGTH 100

// Morse Code enumerator definition using a smaller type
typedef uint8_t MorseCode;

// Function prototypes
void morse_config_save(uint8_t step, uint8_t value);
uint8_t morse_config_state(Event event, uint16_t arg);
void store_morse_code_input(uint8_t presses);
void display_morse_code_message(uint8_t brightness);
void set_morse_speed(uint8_t speed);
void init_message(void);
MorseCode map_button_to_morse(uint8_t presses);
uint8_t morse_state(Event event, uint16_t arg);
uint8_t morse_input_state(Event event, uint16_t arg);

// External variables
extern uint8_t morse_speed;
extern uint8_t message[MAX_MESSAGE_LENGTH];
extern uint8_t message_length;

#endif // MORSE_CODE_H
