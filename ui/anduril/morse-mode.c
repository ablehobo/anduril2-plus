#include "morse-code.h"
#include "misc.h"

uint8_t morse_state(Event event, uint16_t arg) {
    static int8_t speed_direction = 1;

    if (event == EV_enter_state) {
        speed_direction = 1;
        return EVENT_HANDLED;
    } else if (event == EV_1click) {
        set_state(off_state, 0);
        return EVENT_HANDLED;
    } else if (event == EV_2clicks) {
        set_state(battcheck_state, 0);
        return EVENT_HANDLED;
    } else if (event == EV_click1_hold) {
        if (morse_speed > 10) {
            morse_speed -= 1 * speed_direction;
        }
        return EVENT_HANDLED;
    } else if (event == EV_click1_hold_release) {
        speed_direction = -speed_direction;
        save_config();
        return EVENT_HANDLED;
    } else if (event == EV_click2_hold) {
        if (morse_speed < 160) {
            morse_speed += 1 * speed_direction;
        }
        return EVENT_HANDLED;
    } else if (event == EV_click2_hold_release) {
        save_config();
        return EVENT_HANDLED;
    } else if (event == EV_click3_hold) {
        set_morse_speed(DEFAULT_MORSE_SPEED);
        save_config();
        return EVENT_HANDLED;
    } else if (event == EV_click7_hold) {
        push_state(morse_config_state, 0);
        return EVENT_HANDLED;
    }

    return EVENT_NOT_HANDLED;
}


uint8_t morse_config_state(Event event, uint16_t arg) {
    return config_state_base(event, arg, 4, morse_config_save);
}

uint8_t morse_input_state(Event event, uint16_t arg) {
    static uint8_t click_count = 0;

    if (event == EV_enter_state) {
        for (uint8_t i = 0; i < 3; i++) {
            set_level(10);
            nice_delay_ms(50);
            set_level(0);
            nice_delay_ms(50);
        }
        return EVENT_HANDLED;
    }

    if (event == EV_click1_press) {
        click_count++;
        set_level(20);
        nice_delay_ms(100);
        set_level(0);
        return EVENT_HANDLED;
    } else if (event == EV_click1_release) {
        if (click_count > 0) {
            store_morse_code_input(click_count);
            click_count = 0;
            set_level(20);
            nice_delay_ms(200);
            set_level(0);
        }
        return EVENT_HANDLED;
    } else if (event == EV_click1_hold) {
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

void morse_mode_iter(void) {
    if (message_length == INVALID_MORSE_CODE) {
        set_level(10);
        nice_delay_ms(50);
        set_level(0);
        nice_delay_ms(50);
        init_message();
    } else {    
        display_morse_code_message(memorized_level);
        nice_delay_ms(1000); // Adjust delay as needed
    }
}