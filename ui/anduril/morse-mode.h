// morse-mode.h: Header for Morse code mode
#ifndef MORSE_MODE_H
#define MORSE_MODE_H

#include "fsm/spaghetti-monster.h"

// State functions
uint8_t morse_state(Event event, uint16_t arg);
uint8_t morse_input_state(Event event, uint16_t arg);
void morse_config_save(uint8_t step, uint8_t value); // Save configuration for Morse mode
uint8_t morse_config_state(Event event, uint16_t arg); // Configuration state function

#endif // MORSE_MODE_H