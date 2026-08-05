#include "keys.h"

#include "action_layer.h"
#include "action_util.h"
#include "trackpad.h"

uint8_t sticky_mods  = 0;
uint8_t sticky_mods_ = 0;

bool ht_interrupted = false;

void activate_sticky_mods(void) {
    set_weak_mods(get_weak_mods() | sticky_mods);
}

void clear_sticky_mods(void) {
    sticky_mods_ = 0;
    sticky_mods = 0;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    // NOLINTNEXTLINE(bugprone-switch-missing-default-case)
    switch (keycode) {
        case TO_DEF:
            if (record->event.pressed) {
                layer_clear();
            }
            return false;

        case MO_SSLOW:
            return set_trackpad_cpi(CPI_LEVEL_SLOW, record);
        case MO_SMED:
            return set_trackpad_cpi(CPI_LEVEL_MEDIUM, record);
        case MO_SFAST:
            return set_trackpad_cpi(CPI_LEVEL_FAST, record);
        case MO_SBLAZING:
            return set_trackpad_cpi(CPI_LEVEL_BLAZING, record);
    }

    if (record->event.pressed) {
        ht_interrupted = true;
        if ((keycode >= QK_MOMENTARY && keycode <= QK_MOMENTARY_MAX) ||
            (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
            sticky_mods_ = get_mods();
        } else if (sticky_mods != 0) {
            activate_sticky_mods();
        }
    }

    return true;
}

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT));
            return true;

        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        case KC_MINS:
            return true;

        default:
            return false;
    }
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t* record) {
    (void)record;
    switch (keycode) {
        case HT_ALT_R:
        case LT_SYM_ENT:
            return true;
        default:
            return false;
    }
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t* record) {
    (void)record;
    switch (keycode) {
        default:
            return false;
    }
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t* record) {
    (void)record;
    switch (keycode) {
        case HT_ALT_R:
            return 0;
        default:
            return QUICK_TAP_TERM;
    }
}
