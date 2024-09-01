#ifndef MORSE_MODE_H
#define MORSE_MODE_H

#include "fsm/spaghetti-monster.h"
#include <stdint.h>

// State functions for Morse code mode
uint8_t morse_state(Event event, uint16_t arg);
uint8_t morse_config_state(Event event, uint16_t arg);
uint8_t morse_input_state(Event event, uint16_t arg);

// Morse mode iteration function
void morse_mode_iter(void);

#endif // MORSE_MODE_H
