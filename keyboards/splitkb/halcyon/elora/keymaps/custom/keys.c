#include "keys.h"

#include "action_layer.h"
#include "action_util.h"
#include "caps_word.h"
#include "trackpad.h"

uint8_t sticky_mods = 0;

bool ht_interrupted = false;

bool cw_sft(keyrecord_t* record);

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    // NOLINTNEXTLINE(bugprone-switch-missing-default-case)
    switch (keycode) {
        case TO_DEF:
            if (record->event.pressed) {
                layer_clear();
            }
            return false;

        case CW_SFT:
            return cw_sft(record);

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
            sticky_mods = get_mods();
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
        case HT_SYM:
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

bool cw_sft(keyrecord_t* record) {
    static uint16_t timer = 0;
    if (record->event.pressed) {
        timer          = timer_read();
        ht_interrupted = false;
        sticky_mods    = get_mods();
        register_code(KC_LSFT);
    } else {
        unregister_code(KC_LSFT);
        if (!ht_interrupted && timer_elapsed(timer) < TAPPING_TERM) {
            caps_word_toggle();
        }
    }
    return false;
}
