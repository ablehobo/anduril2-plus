// aux-leds.c: Aux LED functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "anduril/aux-leds.h"


#if defined(USE_INDICATOR_LED)
void indicator_led_update(uint8_t mode, uint8_t tick) {
    //uint8_t volts = voltage;  // save a few bytes by caching volatile value
    // turn off when battery is too low
    #ifdef DUAL_VOLTAGE_FLOOR
    if (((voltage < VOLTAGE_LOW) && (voltage > DUAL_VOLTAGE_FLOOR))
        || (voltage < DUAL_VOLTAGE_LOW_LOW)) {
    #else
    if (voltage < VOLTAGE_LOW) {
    #endif
        indicator_led(0);
    }
    //#ifdef USE_INDICATOR_LOW_BAT_WARNING
    #ifndef DUAL_VOLTAGE_FLOOR // this isn't set up for dual-voltage lights like the Sofirn SP10 Pro
    // fast blink a warning when battery is low but not critical
    else if (voltage < VOLTAGE_RED) {
        indicator_led(mode & (((tick & 0b0010)>>1) - 3));
    }
    #endif
    //#endif
    // normal steady output, 0/1/2 = off / low / high
    else if ((mode & 0b00001111) < 3) {
        indicator_led(mode);
    }
    // beacon-like blinky mode
    else {
        #ifdef USE_OLD_BLINKING_INDICATOR

        // basic blink, 1/8th duty cycle
        if (! (tick & 7)) {
            indicator_led(2);
        }
        else {
            indicator_led(0);
        }

        #else

        // fancy blink, set off/low/high levels here:
        static const uint8_t seq[] = {0, 1, 2, 1,  0, 0, 0, 0,
                                      0, 0, 1, 0,  0, 0, 0, 0};
        indicator_led(seq[tick & 15]);

        #endif  // ifdef USE_OLD_BLINKING_INDICATOR
    }
}
#endif

#if defined(USE_AUX_RGB_LEDS) && defined(TICK_DURING_STANDBY)
uint8_t voltage_to_rgb() {
    static const uint8_t levels[] = {
    // voltage, color
            0, 0, // black
        #ifdef DUAL_VOLTAGE_FLOOR
        // AA / NiMH voltages
         9*dV, 1, // R
        10*dV, 2, // R+G
        11*dV, 3, //   G
        12*dV, 4, //   G+B
        13*dV, 5, //     B
        14*dV, 6, // R + B
        16*dV, 7, // R+G+B
        20*dV, 0, // black
        #endif
        // li-ion voltages
        29*dV, 1, // R
        33*dV, 2, // R+G
        35*dV, 3, //   G
        37*dV, 4, //   G+B
        39*dV, 5, //     B
        41*dV, 6, // R + B
        44*dV, 7, // R+G+B  // skip; looks too similar to G+B
          255, 7, // R+G+B
    };
    uint8_t volts = voltage;
    //if (volts < VOLTAGE_LOW) return 0;

    uint8_t i;
    for (i = 0;  volts >= levels[i];  i += 2) {}
    uint8_t color_num = levels[(i - 2) + 1];
    return pgm_read_byte(rgb_led_colors + color_num);
}

#ifdef USE_THERMAL_REGULATION
uint8_t temperature_to_rgb() {
    static const uint8_t temp_levels[] = {
    // temperature in Celsius, color
          0, 6, // R + B => pink/purple  <=50 F
         10, 5, //     B                 (50,60] F
         16, 4, //   G+B => cyan         (60,70] F
         21, 3, //   G                   (70,80] F
         27, 2, // R+G   => yellow       (80,90] F
         32, 1, // R                     >90 F
        255, 1, // R
    };
    int16_t temps = temperature;
    if (temps < 0) return 0;

    uint8_t i;
    for (i = 0; temps >= temp_levels[i]; i += 2) {}
    uint8_t color_num = temp_levels[(i - 2) + 1];
    return pgm_read_byte(rgb_led_colors + color_num);
}
#endif

// do fancy stuff with the RGB aux LEDs
// mode: 0bPPPPCCCC where PPPP is the pattern and CCCC is the color
// arg: time slice number
void rgb_led_update(uint8_t mode, uint16_t arg) {
    static uint8_t rainbow = 0;  // track state of rainbow mode
    static uint8_t frame = 0;  // track state of animation mode

    // turn off aux LEDs when battery is empty
    // (but if voltage==0, that means we just booted and don't know yet)
    uint8_t volts = voltage;  // save a few bytes by caching volatile value
    #ifdef DUAL_VOLTAGE_FLOOR
    if ((volts) && (((voltage < VOLTAGE_LOW) && (voltage > DUAL_VOLTAGE_FLOOR)) || (voltage < DUAL_VOLTAGE_LOW_LOW))) {
    #else
    if ((volts) && (volts < VOLTAGE_LOW)) {
    #endif
        rgb_led_set(0);
        #ifdef USE_BUTTON_LED
        button_led_set(0);
        #endif
        return;
    }

    uint8_t pattern = (mode>>4);  // off, low, high, blinking, breathing
    #ifdef USE_BUTTON_LED
    uint8_t button_pattern = pattern;
    #endif
    uint8_t color = mode & 0x0f;

    // always preview in high mode
    if (setting_rgb_mode_now) { pattern = 2; }

    #ifdef USE_POST_OFF_VOLTAGE
    // use voltage high mode for a few seconds after initial poweroff
    // (but not after changing aux LED settings and other similar actions)
    else if ((arg < (cfg.post_off_voltage * SLEEP_TICKS_PER_SECOND))
          && (ticks_since_on < (cfg.post_off_voltage * SLEEP_TICKS_PER_SECOND))
          && (ticks_since_on > 0)  // don't blink red on 1st frame
        ) {
        // use high mode if regular aux level is high or prev level was high
        pattern = 1 + ((2 == pattern) | (prev_level >= POST_OFF_VOLTAGE_BRIGHTNESS));
        // voltage mode
        color = 9;
    }
    #endif

    const uint8_t *colors = rgb_led_colors + 1;
    uint8_t actual_color = 0;
    if (color < 7) {  // normal color
        actual_color = pgm_read_byte(colors + color);
    }
    else if (color == 7) {  // disco
        rainbow = (rainbow + 1 + pseudo_rand() % 5) % 6;
        actual_color = pgm_read_byte(colors + rainbow);
    }
    else if (color == 8) {  // rainbow
        uint8_t speed = 0x03;  // awake speed
        if (go_to_standby) speed = RGB_RAINBOW_SPEED;  // asleep speed
        if (0 == (arg & speed)) {
            rainbow = (rainbow + 1) % 7;
        }
        actual_color = pgm_read_byte(colors + rainbow);
    }
    else if (color == 9) {  // voltage
        // show actual voltage while asleep...
        if (go_to_standby) {
            // choose a color based on battery voltage
            actual_color = voltage_to_rgb();
        }
        // ... but during preview, cycle colors quickly
        else {
            actual_color = pgm_read_byte(colors + (((arg>>1) % 3) << 1));
        }
    }
    #ifdef USE_THERMAL_REGULATION
    else {   // temperature
        actual_color = temperature_to_rgb();
        if (!go_to_standby) {
            // during preview, flash current temperature's colors quickly
            pattern = (arg >> 1) % 3;
        }
    }
    #endif

    // uses an odd length to avoid lining up with rainbow loop
    static const uint8_t animation[] = {2, 1, 0, 0,  0, 0, 0, 0,  0,
                                        1, 0, 0, 0,  0, 0, 0, 0,  0, 1};
    static const uint8_t animation_breath[] = {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 1, 1,  2, 2,
                                               2, 1, 1, 1,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0};
    // pick a brightness from the animation sequence
    #ifdef USE_BUTTON_LED
    uint8_t blink_animation_done = 0;
    #endif

    // pick a brightness from the animation sequence
    if (pattern == 3) {
        frame = (frame + 1) % sizeof(animation);
        pattern = animation[frame];
        #ifdef USE_BUTTON_LED
        blink_animation_done = 1;
        #endif
    } else if (pattern == 4) {
        frame = (frame + 1) % sizeof(animation_breath);
        pattern = animation_breath[frame];
        #ifdef USE_BUTTON_LED
        blink_animation_done = 1;
        #endif
    }
    #ifdef USE_BUTTON_LED
    if (button_pattern == 3) {
        if (blink_animation_done) {
            button_pattern = pattern;
        } else {
            frame = (frame + 1) % sizeof(animation);
            button_pattern = animation[frame];
        }
    } else if (button_pattern == 4) {
        if (blink_animation_done) {
            button_pattern = pattern;
        } else {
            frame = (frame + 1) % sizeof(animation_breath);
            button_pattern = animation_breath[frame];
        }
    }
    #endif

    uint8_t result;
    switch (pattern) {
        case 0:  // off
            result = 0;
            break;
        case 1:  // low
            result = actual_color;
            break;
        default:  // high
            result = (actual_color << 1);
            break;
    }
    rgb_led_set(result);

    // separate button LED logic here because the button LED may blink while AUX LED doesn't
    #ifdef USE_BUTTON_LED
    button_led_set((button_pattern > 1) ? 2 : button_pattern);
    #endif
}

void rgb_led_voltage_readout(uint8_t bright) {
    uint8_t color = voltage_to_rgb();
    if (bright) color = color << 1;
    rgb_led_set(color);
}
#endif

