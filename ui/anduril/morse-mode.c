// morse-mode.c: Morse code mode for Anduril.

//#include "fsm/spaghetti-monster.h"
#include "anduril/morse-mode.h"
#include "anduril/morse-code.h"
//#include "aux-leds.h"
#include "misc.h"


inline void morse_mode_iter() {
    // Execute Morse code playback in main loop
    display_morse_code_message();
    nice_delay_ms(1000); // Adjust delay as needed
}

// Morse Code State: Handles mode selection and playback
uint8_t morse_state(Event event, uint16_t arg) {
    // 1 click: Turn off Morse mode
    if (event == EV_1click) {
        set_state(off_state, 0);
        return EVENT_HANDLED;
    }
    // 2 clicks: Switch to the next blinkie mode
    else if (event == EV_2clicks) {
        #if defined(USE_BATTCHECK)
            set_state(battcheck_state, 0);
        #elif defined (USE_THERMAL_REGULATION) || defined (USE_BATTCHECK)
            set_state(battcheck_state, 0);
        #elif defined(USE_BEACON_MODE)
            set_state(beacon_state, 0);
        #elif defined(USE_SOS_MODE) && defined(USE_SOS_MODE_IN_BLINKY_GROUP)
            set_state(sos_state, 0);
        #endif
        return EVENT_HANDLED;
    }
    // 7H: Enter Morse code input mode
    else if (event == EV_click7_hold) {
        push_state(morse_input_state, 0);
        //morse_input(event, arg);
        return EVENT_HANDLED;
    }
    // Long press: Playback Morse code message
    else if (event == EV_click1_hold) {
        display_morse_code_message();
        return EVENT_HANDLED;
    }
    return EVENT_NOT_HANDLED;
}


// Morse Code Input Function: Handles user input for Morse code
uint8_t morse_input_state(Event event, uint16_t arg) {
    static uint8_t click_count = 0;

    // Flutter effect when entering Morse input mode
    if (event == EV_enter_state) {
        for (uint8_t i = 0; i < 3; i++) {
            set_level(10); // Set a low level for flutter
            nice_delay_ms(50); // Short delay
            set_level(0);
            nice_delay_ms(50);
        }
        return EVENT_HANDLED;
    }

    // 1 click: Increment click count and confirm with a blink
    if (event == EV_click1_press) {
        click_count++;
        // Blink to confirm input
        set_level(20); // Short confirmation blink
        nice_delay_ms(100);
        set_level(0);
        return EVENT_HANDLED;
    }
    // Button release: Store the character and reset count
    else if (event == EV_click1_release) {
        if (click_count > 0) {
            store_morse_code_input(click_count);
            click_count = 0;
            // Blink to confirm character storage
            set_level(20);
            nice_delay_ms(200);
            set_level(0);
        }
        return EVENT_HANDLED;
    }
    // 1 click + hold: Exit Morse code input mode
    else if (event == EV_click1_hold) {
        // Flutter effect when exiting Morse input mode
        for (uint8_t i = 0; i < 3; i++) {
            set_level(10);
            nice_delay_ms(50);
            set_level(0);
            nice_delay_ms(50);
        }
        set_state(morse_state, 0);
        return EVENT_HANDLED;
    }
    return EVENT_NOT_HANDLED;
}


void morse_config_save(uint8_t step, uint8_t value) {
    if (value) {
        // Item 1: Message Entry
        if (step == 1) {
            store_morse_code_input(value);
        }
        // Item 2: Morse Code Playback Speed
        else if (step == 2) {
            set_morse_speed(value);
        }
    }
}

uint8_t morse_config_state(Event event, uint16_t arg) {
    return config_state_base(event, arg, 2, morse_config_save); // Adjust the step count if necessary
}
