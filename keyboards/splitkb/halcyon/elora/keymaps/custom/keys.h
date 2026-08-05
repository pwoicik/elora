#pragma once

#include <stdint.h>

#include "layers.h" // IWYU pragma: keep
#include "quantum_keycodes.h"

#define HM_C(key) LCTL_T(key)
#define HM_S(key) LSFT_T(key)
#define HM_G(key) LGUI_T(key)
#define HM_A(key) LALT_T(key)
#define HT_ALT_R RALT_T(KC_R)

#define LT_SYM_ENT LT(SYMBOL, KC_ENT)
#define LT_NAV_BSP LT(NAVIGATION, KC_BSPC)
#define LT_NUM_SPC LT(NUMBER, KC_SPC)
#define LT_FUN_TAB LT(FUNCTION, KC_TAB)

enum {
    TO_DEF = SAFE_RANGE,
    MO_SSLOW,
    MO_SMED,
    MO_SFAST,
    MO_SBLAZING,
};

extern uint8_t sticky_mods;
extern uint8_t sticky_mods_;

void activate_sticky_mods(void);
void clear_sticky_mods(void);
