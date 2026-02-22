#pragma once

#include "layers.h" // IWYU pragma: keep
#include "quantum_keycodes.h"

#define HM_C(key) LCTL_T(key)
#define HM_S(key) LSFT_T(key)
#define HM_G(key) LGUI_T(key)
#define HM_A(key) LALT_T(key)
#define HT_ALT_R RALT_T(KC_R)
#define HT_SYM LT(SYMBOL, KC_ENT)
#define SEMI KC_SCLN
#define MO_DEF MO(DEFAULT)

enum {
    TO_DEF = SAFE_RANGE,
    CW_SFT,
    MO_SSLOW,
    MO_SMED,
    MO_SFAST,
    MO_SBLAZING,
};

extern uint8_t sticky_mods;
