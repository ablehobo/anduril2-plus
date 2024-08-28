// aux-leds.h: Aux LED functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#if defined(USE_INDICATOR_LED) && defined(TICK_DURING_STANDBY)
void indicator_led_update(uint8_t mode, uint8_t tick);
#endif
#if defined(USE_AUX_RGB_LEDS) && defined(TICK_DURING_STANDBY)
uint8_t setting_rgb_mode_now = 0;
void rgb_led_update(uint8_t mode, uint16_t arg);
void rgb_led_voltage_readout(uint8_t bright);

#define RGB_RED 0
#define RGB_YELLOW 1
#define RGB_GREEN 2
#define RGB_CYAN 3
#define RGB_BLUE 4
#define RGB_PURPLE 5
#define RGB_WHITE 6

#define RGB_OFF (0<<4)
#define RGB_LOW (1<<4)
#define RGB_HIGH (2<<4)
#define RGB_BLINK (3<<4)
#define RGB_BREATH (4<<4)

/*
 * 0: R
 * 1: RG
 * 2:  G
 * 3:  GB
 * 4:   B
 * 5: R B
 * 6: RGB
 * 7: rainbow
 * 8: voltage
 */
const PROGMEM uint8_t rgb_led_colors[] = {
    0b00000000,  // 0: black
    0b00000001,  // 1: red
    0b00000101,  // 2: yellow
    0b00000100,  // 3: green
    0b00010100,  // 4: cyan
    0b00010000,  // 5: blue
    0b00010001,  // 6: purple
    0b00010101,  // 7: white
};
// intentionally 1 higher than total modes, to make "voltage" easier to reach
// (at Hank's request)
#define RGB_LED_NUM_COLORS 11
#define RGB_LED_NUM_PATTERNS 5
#ifndef RGB_LED_OFF_DEFAULT
#define RGB_LED_OFF_DEFAULT 0x4A  // breath, temperature
//#define RGB_LED_OFF_DEFAULT 0x18  // low, rainbow
#endif
#ifndef RGB_LED_LOCKOUT_DEFAULT
//#define RGB_LED_LOCKOUT_DEFAULT 0x39  // blinking, voltage
//#define RGB_LED_LOCKOUT_DEFAULT 0x37  // blinking, disco
#define RGB_LED_LOCKOUT_DEFAULT 0x48 //breath, rainbow
#endif
#ifndef RGB_RAINBOW_SPEED
#define RGB_RAINBOW_SPEED 0x04  // change color every 4 frames
#endif
#endif

//#define USE_OLD_BLINKING_INDICATOR
//#define USE_FANCIER_BLINKING_INDICATOR
#ifdef USE_INDICATOR_LED
    // bits 2-3 control lockout mode
    // bits 0-1 control "off" mode
    // modes are: 0=off, 1=low, 2=high, 3=blinking (if TICK_DURING_STANDBY enabled)
    #ifndef INDICATOR_LED_DEFAULT_MODE
        #ifdef USE_INDICATOR_LED_WHILE_RAMPING
            #define INDICATOR_LED_DEFAULT_MODE ((2<<2) + 1)
        #else
            #define INDICATOR_LED_DEFAULT_MODE ((3<<2) + 1)
        #endif
    #endif
#endif

