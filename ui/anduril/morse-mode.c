// morse-mode.c: Morse code mode for Anduril.

#include "anduril/morse-mode.h"
#include "anduril/morse-code.h"
#include "misc.h"

inline void morse_mode_iter() {
    if (message_length == 254) {
        init_message(); // Initialize the message
    }
    // Execute Morse code playback in main loop
    display_morse_code_message(memorized_level);
    nice_delay_ms(1000); // Adjust delay as needed
}

// Morse Code State: Handles mode selection and playback
uint8_t morse_state(Event event, uint16_t arg) {
    static int8_t speed_direction = 1;

    // Enter Morse code mode
    if (event == EV_enter_state) {
        speed_direction = 1;  // Default to increasing speed
        return EVENT_HANDLED;
    }
    // 1 click: Turn off Morse mode
    else if (event == EV_1click) {
        set_state(off_state, 0);
        return EVENT_HANDLED;
    }
    // 2 clicks: Switch to the next blinkie mode
    else if (event == EV_2clicks) {
        set_state(beacon_state, 0);
        return EVENT_HANDLED;
    }
    // Hold: Increase speed
    else if (event == EV_click1_hold) {
        if (morse_speed > 60) {  // Avoid going too fast
            morse_speed -= 1.5 * speed_direction;  // Decrease speed more slowly
        }
        return EVENT_HANDLED;
    }
    // Hold release: Reverse speed direction (for next hold)
    else if (event == EV_click1_hold_release) {
        speed_direction = -speed_direction;
        save_config();  // Save the current speed setting
        return EVENT_HANDLED;
    }
    // Hold: Decrease speed
    else if (event == EV_click2_hold) {
        if (morse_speed < 200) {  // Avoid going too slow
            morse_speed += 1.5 * speed_direction;  // Increase speed more slowly
        }
        return EVENT_HANDLED;
    }
    // Hold release: Save the current speed setting
    else if (event == EV_click2_hold_release) {
        save_config();
        return EVENT_HANDLED;
    }
    // Reset speed
    else if (event == EV_click3_hold) {
        set_morse_speed(DEFAULT_MORSE_SPEED);
        save_config();
        return EVENT_HANDLED;
    }
    // Enter the 7H menu for configuring Morse code options
    else if (event == EV_click7_hold) {
        push_state(morse_config_state, 0);
        return EVENT_HANDLED;
    }

    return EVENT_NOT_HANDLED;
}

// The main configuration function using `config_state_base`
uint8_t morse_config_state(Event event, uint16_t arg) {
    return config_state_base(event, arg, 3, morse_config_save);  // Three steps: add character, new message, speed
}
