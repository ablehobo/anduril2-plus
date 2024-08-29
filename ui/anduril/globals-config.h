#ifndef GLOBALS_CONFIG_H
#define GLOBALS_CONFIG_H

#pragma once

#include <stdint.h>       // For uint8_t, uint16_t
#include "fsm/events.h"
#include "config-mode.h"  // For config_state_base and related types

typedef enum {
    globals_cfg_zero = 0,
    #if defined(USE_CHANNEL_MODE_ARGS) && defined(USE_STEPPED_TINT_RAMPING)
    tint_style_config_step,
    #endif
    #ifdef USE_JUMP_START
    jump_start_config_step,
    #endif
    #ifdef NUM_MODE
    num_mode_config_step,
    #endif
    globals_config_num_steps
} globals_config_steps_e;

//void globals_config_save(uint8_t step, uint8_t value);
//uint8_t globals_config_state(Event event, uint16_t arg);

void globals_config_save(uint8_t step, uint8_t value) {
    if (0) {}
    #if defined(USE_CHANNEL_MODE_ARGS) && defined(USE_STEPPED_TINT_RAMPING)
    else if (step == tint_style_config_step) { cfg.tint_ramp_style = value; }
    #endif
    #ifdef USE_JUMP_START
    else if (step == jump_start_config_step) { cfg.jump_start_level = value; }
    #endif
    #ifdef NUM_MODE
    else if (step == num_mode_config_step) { cfg.num_mode = value; }
    #endif
}

uint8_t globals_config_state(Event event, uint16_t arg) {
    return config_state_base(event, arg,
                             globals_config_num_steps - 1,
                             globals_config_save);
}


#endif // GLOBALS_CONFIG_H
