#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "action.h"
#include "action_layer.h"
#include "action_tapping.h"
#include "action_util.h"
#include "caps_word.h"
#include "config.h"
#include "info_config.h"
#include "keyboard.h"
#include "keycodes.h"
#include "pointing_device.h"
#include "process_tap_dance.h"
#include "progmem.h"
#include "quantum.h"
#include "quantum_keycodes.h"
#include "raw_hid.h"
#include "timer.h"
#include "usb_descriptor.h"
#include "util.h"

#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
#    include "pointing_device_auto_mouse.h"
#endif /* ifdef  */

enum layers {
    DEFAULT = 0,
    LOWER,
    SYMBOL,
    FUNCTION,
    MAGIC,

    GAME,
    MOUSE,
};

const char *layer_names[] = {"Default", "Lower", "Symbol", "Function", "Magic", "Game", "Mouse"};

#define HM_C(key) LCTL_T(key)
#define HM_S(key) LSFT_T(key)
#define HM_G(key) LGUI_T(key)
#define HM_A(key) LALT_T(key)
#define SEMI KC_SCLN
#define TO_DEF TO(DEFAULT)

enum custom_keycodes {
    CW_SFT = SAFE_RANGE,
    HT_FUNC,
    HT_MAGIC,
    HT_LOWER,
    HT_SYM,
    MO_SSLOW,
    MO_SMED,
    MO_SFAST,
    MO_SBLAZING,
    TO_GAME,
};

enum {
    HSH_DEF,
    TD_MAGIC,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEFAULT] = LAYOUT_elora_hlc(
     KC_EQL,       KC_1,         KC_2,         KC_3,         KC_4,         KC_5,                                                                   KC_6,         KC_7,         KC_8,         KC_9,         KC_0,         KC_MINS,
     KC_TAB,       KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,                                                                   KC_Y,         KC_U,         KC_I,         KC_O,         KC_P,         KC_BSLS,
     KC_ESC,       HM_C(KC_A),   HM_S(KC_S),   HM_G(KC_D),   HM_A(KC_F),   KC_G,                                                                   KC_H,         HM_A(KC_J),   HM_G(KC_K),   HM_S(KC_L),   HM_C(SEMI),   KC_QUOT,
     KC_GRV,       KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,         CW_SFT,       KC_DEL,         HT_FUNC,      CW_SFT,       KC_N,         KC_M,         KC_COMM,      KC_DOT,       KC_SLSH,      TD(TD_MAGIC),
                                               KC_NO,        HT_FUNC,      HT_LOWER,     KC_SPC,       KC_BSPC,        HT_SYM ,      KC_RALT,      HT_LOWER,     HT_FUNC,      KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                                                              KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO
    ),

    [LOWER] = LAYOUT_elora_hlc(
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_HOME,                                                                KC_LPRN,      KC_NUM,       KC_PEQL,      KC_PSLS,      KC_PAST,      KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_UP,        KC_NO,        KC_END,                                                                 KC_RPRN,      KC_P7,        KC_P8,        KC_P9,        KC_PMNS,      KC_PSCR,
     TO(DEFAULT),  KC_NO,        KC_LEFT,      KC_DOWN,      KC_RIGHT,     KC_PGUP,                                                                KC_PERC,      HM_A(KC_P4),  HM_G(KC_P5),  HM_S(KC_P6),  HM_C(KC_PPLS),KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_PGDN,      KC_NO,        KC_DEL,         KC_NO,        KC_NO,        KC_COMM,      KC_P1,        KC_P2,        KC_P3,        KC_PENT,      TD(TD_MAGIC),
                                               KC_NO,        KC_NO,        KC_NO,        KC_SPC,       KC_BSPC,        KC_ENT,       KC_NO,        KC_NO,        KC_P0,        KC_PDOT,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                                                              KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO
    ),

    [SYMBOL] = LAYOUT_elora_hlc(
     KC_GRAVE,     KC_LBRC,      KC_LPRN,      KC_RPRN,      KC_RBRC,      KC_DOT,                                                                 KC_NO,        KC_NUM,       KC_PEQL,      KC_PSLS,      KC_PAST,      KC_NO,
     KC_EXLM,      KC_COMM,      KC_LCBR,      KC_RCBR,      KC_SCLN,      KC_QUES,                                                                KC_GRAVE,     KC_P7,        KC_P8,        KC_P9,        KC_PMNS,      KC_PSCR,
     TD(HSH_DEF),  KC_CIRC,      KC_EQL,       KC_UNDS,      KC_DOLLAR,    KC_ASTR,                                                                KC_DQT,       KC_P4,        KC_P5,        KC_P6,        KC_PPLS,      KC_NO,
     KC_TILDE,     KC_LT,        KC_PIPE,      KC_MINS,      KC_GT,        KC_SLSH,      KC_BSLS,      KC_AT,          KC_NO,        KC_NO,        KC_QUOT,      KC_P1,        KC_P2,        KC_P3,        KC_PENT,      TD(TD_MAGIC),
                                               KC_AMPR,      KC_PLUS,      KC_NO,        KC_PERC,      KC_COLON,       KC_NO,        KC_NO,        KC_NO,        KC_P0,        KC_PDOT,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                                                              KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO
    ),

    [FUNCTION] = LAYOUT_elora_hlc(
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                                  KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_NO,        KC_F9,        KC_F10,       KC_F11,       KC_F12,       KC_NO,                                                                  KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     TO_DEF,       KC_F5,        KC_F6,        KC_F7,        KC_F8,        KC_NO,                                                                  KC_NO,        KC_LALT,      KC_LGUI,      KC_LSFT,      KC_LCTL,      KC_NO,
     KC_NO,        KC_F1,        KC_F2,        KC_F3,        KC_F4,        KC_NO,        KC_NO,        KC_NO,          KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        TD(TD_MAGIC),
                                               KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,          KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                                                              KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO
    ),

    [MAGIC] = LAYOUT_elora_hlc(
     TO_DEF,       TO(LOWER),    TO(SYMBOL),   TO_GAME,      TO(FUNCTION), KC_NO,                                                                  KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                                  KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                                  RM_TOGG,      RM_SATU,      RM_HUEU,      RM_VALU,      RM_NEXT,      KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,          KC_NO,        KC_NO,        KC_NO,        RM_SATD,      RM_HUED,      RM_VALD,      RM_PREV,      TO_DEF,
                                               KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,          KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                                                              KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO
    ),

    [GAME] = LAYOUT_elora_hlc(
     KC_ESC,       KC_I,         KC_2,         KC_3,         KC_4,         KC_5,                                                                   KC_F1,        KC_F2,        KC_F3,        KC_F4,        KC_F5,        KC_F6,
     KC_NO,        KC_TAB,       KC_Q,         KC_1,         KC_E,         KC_R,                                                                   KC_6,         KC_7,         KC_8,         KC_9,         KC_0,         TO_DEF,
     KC_G,         KC_LSFT,      KC_A,         KC_W,         KC_D,         KC_F,                                                                   TO_DEF,       TO_DEF,       TO_DEF,       TO_DEF,       TO_DEF,       TO_DEF,
     KC_B,         KC_LCTL,      KC_Z,         KC_S,         KC_C,         KC_V,         KC_LALT,      KC_ENT,         TO_DEF,       TO_DEF,       TO_DEF,       TO_DEF,       TO_DEF,       TO_DEF,       TO_DEF,       TO_DEF,
                                               KC_M,         KC_T,         KC_X,         KC_SPC,       KC_NO,          TO_DEF,       TO_DEF,       TO_DEF,       TO_DEF,       TO_DEF,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                                                              KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO
    ),

    [MOUSE] = LAYOUT_elora_hlc(
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                                  KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_NO,        MO_SSLOW,     MO_SMED,      MO_SFAST,     MO_SBLAZING,  KC_NO,                                                                  KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_ESC,       KC_LCTL,      KC_LSFT,      KC_LGUI,      KC_LALT,      KC_NO,                                                                  KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,          KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
                                               KC_NO,        KC_NO,        MS_BTN2,      MS_BTN1,      MS_BTN3,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                                                              KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO
    ),
};
// clang-format on

bool hold_tap_key_func(uint8_t key, void (*func)(void), keyrecord_t *record);
bool hold_tap_layer(int layer, keyrecord_t *record);
bool hold_tap_key_layer(uint8_t key, int layer, keyrecord_t *record);
bool set_trackpad_cpi(uint16_t cpi, keyrecord_t *record);
bool hid_send_message(char const *message_type, char const *message);

// modifiers that are active until layer is switched back to default
uint8_t sticky_mods = 0;

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t cur_layer = get_highest_layer(state);
    if (cur_layer == DEFAULT) {
        sticky_mods = 0;
        clear_weak_mods();
        send_keyboard_report();
    }
    hid_send_message("LAYER", layer_names[cur_layer]);
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CW_SFT:
            return hold_tap_key_func(KC_LSFT, caps_word_toggle, record);

        case HT_SYM:
            return hold_tap_key_layer(KC_ENT, SYMBOL, record);

        case HT_FUNC:
            return hold_tap_layer(FUNCTION, record);

        case HT_LOWER:
            return hold_tap_layer(LOWER, record);

        case HT_MAGIC:
            return hold_tap_layer(MAGIC, record);

        case MO_SSLOW:
            return set_trackpad_cpi(200, record);
        case MO_SMED:
            return set_trackpad_cpi(400, record);
        case MO_SFAST:
            return set_trackpad_cpi(800, record);
        case MO_SBLAZING:
            return set_trackpad_cpi(1200, record);

        case TO_GAME:
            if (record->event.pressed) {
                layer_move(GAME);
            }
            return false;
    }

    if (sticky_mods != 0) {
        set_weak_mods(sticky_mods);
    }
    return true;
}

bool hold_tap_key_func(uint8_t key, void (*func)(void), keyrecord_t *record) {
    static uint16_t timer = 0;
    if (record->event.pressed) {
        timer       = timer_read();
        sticky_mods = get_mods();
        register_code(key);
    } else {
        unregister_code(key);
        if (timer_elapsed(timer) < TAPPING_TERM) {
            func();
        }
    }
    return false;
}

bool hold_tap_layer(int layer, keyrecord_t *record) {
    static uint16_t timer = 0;
    if (record->event.pressed) {
        timer       = timer_read();
        sticky_mods = get_mods();
        layer_on(layer);
    } else {
        if (timer_elapsed(timer) >= TAPPING_TERM) {
            layer_off(layer);
        }
    }
    return false;
}

bool hold_tap_key_layer(uint8_t key, int layer, keyrecord_t *record) {
    static uint16_t timer = 0;
    if (record->event.pressed) {
        timer       = timer_read();
        sticky_mods = get_mods();
    } else {
        if (timer_elapsed(timer) < TAPPING_TERM) {
            tap_code(key);
        } else {
            layer_on(layer);
        }
    }
    return false;
}

bool set_trackpad_cpi(uint16_t cpi, keyrecord_t *record) {
    if (record->event.pressed) {
        pointing_device_set_cpi(cpi);
    }
    return false;
}

void keyboard_post_init_user(void) {
    pointing_device_set_cpi(400);
}

void pointing_device_init_user(void) {
#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
    set_auto_mouse_layer(MOUSE);
    set_auto_mouse_enable(true);
#endif /* ifdef  */
}

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool       is_press_action;
    td_state_t state;
} td_tap_t;

td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) {
            return TD_SINGLE_TAP;
        } else {
            return TD_SINGLE_HOLD;
        }
    } else if (state->count == 2) {
        if (state->interrupted) {
            return TD_DOUBLE_SINGLE_TAP;
        } else if (state->pressed) {
            return TD_DOUBLE_HOLD;
        } else {
            return TD_DOUBLE_TAP;
        }
    }

    if (state->count == 3) {
        if (state->interrupted || !state->pressed) {
            return TD_TRIPLE_TAP;
        } else {
            return TD_TRIPLE_HOLD;
        }
    } else {
        return TD_UNKNOWN;
    }
}

static td_tap_t td_tap_state = {
    .is_press_action = true,
    .state           = TD_NONE,
};

void magic_dance_finished(tap_dance_state_t *state, void *user_data) {
    td_tap_state.state = cur_dance(state);
    switch (td_tap_state.state) {
        case TD_SINGLE_HOLD:
        case TD_DOUBLE_TAP:
            layer_on(MAGIC);
            break;

        default:
            break;
    }
}

void magic_dance_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_tap_state.state) {
        case TD_SINGLE_HOLD:
            layer_off(MAGIC);
            break;

        default:
            break;
    }
    td_tap_state.state = TD_NONE;
}

tap_dance_action_t tap_dance_actions[] = {
    [HSH_DEF]  = ACTION_TAP_DANCE_LAYER_MOVE(KC_HASH, DEFAULT),
    [TD_MAGIC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, magic_dance_finished, magic_dance_reset),
};

bool hid_send_message(char const *message_type, char const *message) {
    static uint8_t buf[RAW_EPSIZE];

    size_t type_len = strlen(message_type);
    size_t message_len;
    if (message == NULL) {
        message_len = 0;
    } else {
        message_len = strlen(message);
    }
    size_t report_count = CEILING(message_len, RAW_EPSIZE);
    if (type_len > RAW_EPSIZE - 1) {
        return false;
    }
    if (report_count > 255) {
        return false;
    }
    memset(buf, 0, RAW_EPSIZE);
    buf[0] = report_count;
    memcpy(buf + 1, message_type, type_len);
    raw_hid_send(buf, RAW_EPSIZE);

    for (size_t i = 0; i < report_count; ++i) {
        memset(buf, 0, RAW_EPSIZE);
        size_t offset = (i * RAW_EPSIZE);
        memcpy(buf, message + offset, MIN(message_len - offset, RAW_EPSIZE));
        raw_hid_send(buf, RAW_EPSIZE);
    }

    return true;
}
