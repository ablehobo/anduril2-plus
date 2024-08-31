// sos-mode.c: SOS mode for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "anduril/sos-mode.h"

#ifdef USE_SOS_MODE_IN_BLINKY_GROUP
uint8_t sos_state(Event event, uint16_t arg) {
    // 1 click: off
    if (event == EV_1click) {
        set_state(off_state, 0);
        return EVENT_HANDLED;
    }
    // 2 clicks: next blinky mode
    else if (event == EV_2clicks) {
        #if defined(USE_MORSE_MODE)
        set_state(morse_state, 0);
        #elif defined(USE_BATTCHECK_MODE)
        set_state(battcheck_state, 0);
        #elif defined(USE_THERMAL_REGULATION)
        set_state(tempcheck_state, 0);
        #elif defined(USE_BEACON_MODE)
        set_state(beacon_state, 0);
        #endif
        return EVENT_HANDLED;
    }
    return EVENT_NOT_HANDLED;
}
#endif

void sos_blink(uint8_t num, uint8_t dah) {
    #define DIT_LENGTH 200
    for (; num > 0; num--) {
        set_level(memorized_level);
        nice_delay_ms(DIT_LENGTH);
        if (dah) {  // dah is 3X as long as a dit
            nice_delay_ms(DIT_LENGTH*2);
        }
        set_level(0);
        // one "off" dit between blinks
        nice_delay_ms(DIT_LENGTH);
    }
    // three "off" dits (or one "dah") between letters
    nice_delay_ms(DIT_LENGTH*2);
}

inline void sos_mode_iter() {
    // Spell "I LUV U" in Morse code

    // I: ..
    sos_blink(2, 0);  // I
    nice_delay_ms(2000);

    // L: .-..
    sos_blink(1, 0);  // .
    sos_blink(1, 1);  // -
    sos_blink(2, 0);  // ..
    nice_delay_ms(2000);

    // U: ..-
    sos_blink(2, 0);  // ..
    sos_blink(1, 1);  // -
    nice_delay_ms(2000);

    // V: ...-
    sos_blink(3, 0);  // ...
    sos_blink(1, 1);  // -
    nice_delay_ms(2000);

    // U: ..-
    sos_blink(2, 0);  // ..
    sos_blink(1, 1);  // -
    nice_delay_ms(2000);
}

