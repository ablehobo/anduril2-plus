// morse-mode.h: Header for Morse code mode
#ifndef MORSE_MODE_H
#define MORSE_MODE_H

#include "fsm/spaghetti-monster.h"

// State functions
uint8_t morse_state(Event event, uint16_t arg);
uint8_t morse_input_state(Event event, uint16_t arg);

#endif // MORSE_MODE_H
