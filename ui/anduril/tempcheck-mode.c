// tempcheck-mode.c: Temperature check mode for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "anduril/tempcheck-mode.h"

uint8_t tempcheck_state(Event event, uint16_t arg) {
    // 1 click: off
    if (event == EV_1click) {
        set_state(off_state, 0);
        return EVENT_HANDLED;
    }
    // 2 clicks: next blinky mode
    else if (event == EV_2clicks) {
        #if defined(USE_BEACON_MODE)
        set_state(beacon_state, 0);
        #elif defined(USE_SOS_MODE) && defined(USE_SOS_MODE_IN_BLINKY_GROUP)
        set_state(sos_state, 0);
        #elif defined(USE_MORSE_MODE)
        set_state(morse_state, 0);
        #elif defined(USE_BATTCHECK)
        set_state(battcheck_state, 0);
        #elif defined(USE_THERMAL_REGULATION)
        set_state(tempcheck_state, 0);
        #endif
        return EVENT_HANDLED;
    }
    // 7H: thermal config mode
    else if (event == EV_click7_hold) {
        push_state(thermal_config_state, 0);
        return EVENT_HANDLED;
    }
    return EVENT_NOT_HANDLED;
}

void thermal_config_save(uint8_t step, uint8_t value) {
    if (value) {
        // item 1: calibrate room temperature
        if (step == 1) {
            int8_t rawtemp = temperature - cfg.therm_cal_offset;
            cfg.therm_cal_offset = value - rawtemp;
            adc_reset = 2;  // invalidate all recent temperature data
        }

        // item 2: set maximum heat limit
        #ifdef USE_THERMAL_REGULATION
        else if (step == 2) {
            cfg.therm_ceil = 30 + value - 1;
        }
        #endif

        // item 3: toggle temperature unit (Celsius or Fahrenheit)
        else if (step == 3) {
            cfg.temp_unit = value;  // 1 for °C, 2 for °F
        }
    }
    #ifdef USE_THERMAL_REGULATION
        if (cfg.therm_ceil > MAX_THERM_CEIL) cfg.therm_ceil = MAX_THERM_CEIL;
    #endif
}

uint8_t thermal_config_state(Event event, uint16_t arg) {
    return config_state_base(event, arg,
                             3, thermal_config_save);  // 3 steps now
}

