// misc.h: Misc extra functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#ifndef BLIP_LEVEL
#define BLIP_LEVEL  0
#endif

//void blink_confirm(uint8_t num);  // no longer used
void blink_once();
void blink_some(uint8_t times);
void blip();
void blip_ms(uint8_t ms);
