#include QMK_KEYBOARD_H

enum layers {
    DEFAULT = 0,
    LOWER,
    SYMBOL,
    GAME,
    FUNCTION,
    MAGIC,
};

#define HOME_A  LCTL_T(KC_A)
#define HOME_S  LSFT_T(KC_S)
#define HOME_D  LGUI_T(KC_D)
#define HOME_F  LALT_T(KC_F)
#define HOME_J  LALT_T(KC_J)
#define HOME_K  LGUI_T(KC_K)
#define HOME_L  LSFT_T(KC_L)
#define HOME_SCLN LCTL_T(KC_SCLN)

#define SYM_ENT  LT(SYMBOL, KC_ENT)

enum custom_keycodes {
    CW_SFT = SAFE_RANGE,
    LOWER_RALT,
    HT_FUNCTION,
    HT_MAGIC,
};

enum {
    TD_TAP_DANCE,
};

tap_dance_action_t tap_dance_actions[] = {
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t cw_timer = 0;

    switch (keycode) {
        case CW_SFT:
            if (record->event.pressed) {
                cw_timer = timer_read();
                register_code(KC_LSFT);
            } else {
                unregister_code(KC_LSFT);
                if (timer_elapsed(cw_timer) < TAPPING_TERM) {
                    caps_word_toggle();
                }
            }
            return false;

        case LOWER_RALT:
            if (record->event.pressed) {
                cw_timer = timer_read();
                register_code(KC_RALT);
            } else {
                unregister_code(KC_RALT);
                if (timer_elapsed(cw_timer) < TAPPING_TERM) {
                    layer_on(LOWER);
                }
            }
            return false;

        case HT_FUNCTION:
            if (record->event.pressed) {
                cw_timer = timer_read();
                layer_on(FUNCTION);
            } else {
                if (timer_elapsed(cw_timer) >= TAPPING_TERM) {
                    layer_off(FUNCTION);
                }
            }
            return false;

        case HT_MAGIC:
            if (record->event.pressed) {
                cw_timer = timer_read();
                layer_on(MAGIC);
            } else {
                if (timer_elapsed(cw_timer) >= TAPPING_TERM) {
                    layer_off(MAGIC);
                }
            }
            return false;
    }
    return true;
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEFAULT] = LAYOUT_elora_hlc(
     KC_EQL,       KC_1,         KC_2,         KC_3,         KC_4,         KC_5,                                                                   KC_6,         KC_7,         KC_8,         KC_9,         KC_0,         KC_MINS,
     KC_TAB,       KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,                                                                   KC_Y,         KC_U,         KC_I,         KC_O,         KC_P,         KC_BSLS,
     KC_ESC,       HOME_A,       HOME_S,       HOME_D,       HOME_F,       KC_G,                                                                   KC_H,         HOME_J,       HOME_K,       HOME_L,       HOME_SCLN,    KC_QUOT,
     KC_GRV,       KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,         CW_SFT,       KC_DEL,         HT_FUNCTION,  CW_SFT,       KC_N,         KC_M,         KC_COMM,      KC_DOT,       KC_SLSH,      HT_MAGIC,
                                               KC_NO,        KC_NO,        KC_NO,        KC_SPC,       KC_BSPC,        SYM_ENT,      LOWER_RALT,   KC_NO,        KC_NO,        KC_NO,
     KC_MUTE,      KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                                                              KC_MUTE,      KC_NO,        KC_NO,        KC_NO,        KC_NO
    ),

    [LOWER] = LAYOUT_elora_hlc(
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_HOME,                                                                KC_LPRN,      KC_NUM,       KC_PEQL,      KC_PSLS,      KC_PAST,      KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_UP,        KC_NO,        KC_END,                                                                 KC_RPRN,      KC_P7,        KC_P8,        KC_P9,        KC_PMNS,      KC_PSCR,
     TO(DEFAULT),  KC_NO,        KC_LEFT,      KC_DOWN,      KC_RIGHT,     KC_PGUP,                                                                KC_PERC,      KC_P4,        KC_P5,        KC_P6,        KC_PPLS,      KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_PGDN,      KC_NO,        KC_DEL,         KC_NO,        KC_NO,        KC_COMM,      KC_P1,        KC_P2,        KC_P3,        KC_PENT,      KC_NO,
                                               KC_NO,        KC_NO,        KC_NO,        KC_SPC,       KC_BSPC,        KC_ENT,       KC_NO,        KC_NO,        KC_P0,        KC_PDOT,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                                                              KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO
    ),

    [SYMBOL] = LAYOUT_elora_hlc(
     KC_GRAVE,     KC_LBRC,      KC_LPRN,      KC_RPRN,      KC_RBRC,      KC_DOT,                                                                 KC_NO,        KC_NUM,       KC_PEQL,      KC_PSLS,      KC_PAST,      KC_NO,
     KC_EXLM,      KC_COMM,      KC_LCBR,      KC_RCBR,      KC_SCLN,      KC_QUES,                                                                KC_GRAVE,     KC_P7,        KC_P8,        KC_P9,        KC_PMNS,      KC_PSCR,
     KC_HASH,      KC_CIRC,      KC_EQL,       KC_UNDS,      KC_DOLLAR,    KC_ASTR,                                                                KC_DQT,       KC_P4,        KC_P5,        KC_P6,        KC_PPLS,      KC_NO,
     KC_TILDE,     KC_LT,        KC_PIPE,      KC_MINS,      KC_GT,        KC_SLSH,      KC_BSLS,      KC_AT,          KC_NO,        KC_NO,        KC_QUOT,      KC_P1,        KC_P2,        KC_P3,        KC_PENT,      KC_NO,
                                               KC_AMPR,      KC_PLUS,      KC_NO,        KC_PERC,      KC_COLON,       KC_NO,        KC_NO,        KC_NO,        KC_P0,        KC_PDOT,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                                                              KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO
    ),

    [GAME] = LAYOUT_elora_hlc(
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                                  KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                                  KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                                  KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,          KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
                                               KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,          KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                                                              KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO
    ),

    [FUNCTION] = LAYOUT_elora_hlc(
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                                  KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_NO,        KC_F9,        KC_F10,       KC_F11,       KC_F12,       KC_NO,                                                                  KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_NO,        KC_F5,        KC_F6,        KC_F7,        KC_F8,        KC_NO,                                                                  KC_NO,        KC_RSFT,      KC_RCTL,      KC_LALT,      KC_RGUI,      KC_NO,
     KC_NO,        KC_F1,        KC_F2,        KC_F3,        KC_F4,        KC_NO,        KC_NO,        KC_NO,          KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
                                               KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,          KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                                                              KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO
    ),

    [MAGIC] = LAYOUT_elora_hlc(
     TO(DEFAULT),  TO(LOWER),    TO(SYMBOL),   TO(GAME),     TO(FUNCTION), KC_NO,                                                                  KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                                  KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                                  RM_TOGG,      RM_SATU,      RM_HUEU,      RM_VALU,      RM_NEXT,      KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,          KC_NO,        KC_NO,        KC_NO,        RM_SATD,      RM_HUED,      RM_VALD,      RM_PREV,      KC_NO,
                                               KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,          KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                                                              KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO
    ),
};
