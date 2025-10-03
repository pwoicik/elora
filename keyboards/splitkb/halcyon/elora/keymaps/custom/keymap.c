#include "keycodes.h"
#include "pointing_device.h"
#include "process_tap_dance.h"
#include QMK_KEYBOARD_H

enum layers {
    DEFAULT = 0,
    LOWER,
    SYMBOL,
    GAME,
    FUNCTION,
    MAGIC,

    MOUSE,
};

#define HM_C(key) LCTL_T(key)
#define HM_S(key) LSFT_T(key)
#define HM_G(key) LGUI_T(key)
#define HM_A(key) LALT_T(key)
#define SEMI KC_SCLN

#define SYM_ENT LT(SYMBOL, KC_ENT)

enum custom_keycodes {
    CW_SFT = SAFE_RANGE,
    HT_FUNCTION,
    HT_MAGIC,
    MO_SSLOW,
    MO_SMED,
    MO_SFAST,
    MO_SBLAZING,
    HT_LOWER,
};

enum {
    HSH_DEF,
};

tap_dance_action_t tap_dance_actions[] = {
    [HSH_DEF] = ACTION_TAP_DANCE_LAYER_MOVE(KC_HASH, DEFAULT),
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEFAULT] = LAYOUT_elora_hlc(
     KC_EQL,       KC_1,         KC_2,         KC_3,         KC_4,         KC_5,                                                                   KC_6,         KC_7,         KC_8,         KC_9,         KC_0,         KC_MINS,
     KC_TAB,       KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,                                                                   KC_Y,         KC_U,         KC_I,         KC_O,         KC_P,         KC_BSLS,
     KC_ESC,       HM_C(KC_A),   HM_S(KC_S),   HM_G(KC_D),   HM_A(KC_F),   KC_G,                                                                   KC_H,         HM_A(KC_J),   HM_G(KC_K),   HM_S(KC_L),   HM_C(SEMI),   KC_QUOT,
     KC_GRV,       KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,         CW_SFT,       KC_DEL,         HT_FUNCTION,  CW_SFT,       KC_N,         KC_M,         KC_COMM,      KC_DOT,       KC_SLSH,      HT_MAGIC,
                                               KC_NO,        KC_NO,        HT_LOWER,     KC_SPC,       KC_BSPC,        SYM_ENT,      KC_RALT,      HT_LOWER,     KC_NO,        KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                                                              KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO
    ),

    [LOWER] = LAYOUT_elora_hlc(
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_HOME,                                                                KC_LPRN,      KC_NUM,       KC_PEQL,      KC_PSLS,      KC_PAST,      KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_UP,        KC_NO,        KC_END,                                                                 KC_RPRN,      KC_P7,        KC_P8,        KC_P9,        KC_PMNS,      KC_PSCR,
     TO(DEFAULT),  KC_NO,        KC_LEFT,      KC_DOWN,      KC_RIGHT,     KC_PGUP,                                                                KC_PERC,      KC_P4,        KC_P5,        KC_P6,        KC_PPLS,      KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_PGDN,      KC_NO,        KC_DEL,         KC_NO,        KC_NO,        KC_COMM,      KC_P1,        KC_P2,        KC_P3,        KC_PENT,      HT_MAGIC,
                                               KC_NO,        KC_NO,        KC_NO,        KC_SPC,       KC_BSPC,        KC_ENT,       KC_NO,        KC_NO,        KC_P0,        KC_PDOT,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                                                              KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO
    ),

    [SYMBOL] = LAYOUT_elora_hlc(
     KC_GRAVE,     KC_LBRC,      KC_LPRN,      KC_RPRN,      KC_RBRC,      KC_DOT,                                                                 KC_NO,        KC_NUM,       KC_PEQL,      KC_PSLS,      KC_PAST,      KC_NO,
     KC_EXLM,      KC_COMM,      KC_LCBR,      KC_RCBR,      KC_SCLN,      KC_QUES,                                                                KC_GRAVE,     KC_P7,        KC_P8,        KC_P9,        KC_PMNS,      KC_PSCR,
     TD(HSH_DEF),  KC_CIRC,      KC_EQL,       KC_UNDS,      KC_DOLLAR,    KC_ASTR,                                                                KC_DQT,       KC_P4,        KC_P5,        KC_P6,        KC_PPLS,      KC_NO,
     KC_TILDE,     KC_LT,        KC_PIPE,      KC_MINS,      KC_GT,        KC_SLSH,      KC_BSLS,      KC_AT,          KC_NO,        KC_NO,        KC_QUOT,      KC_P1,        KC_P2,        KC_P3,        KC_PENT,      HT_MAGIC,
                                               KC_AMPR,      KC_PLUS,      KC_NO,        KC_PERC,      KC_COLON,       KC_NO,        KC_NO,        KC_NO,        KC_P0,        KC_PDOT,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                                                              KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO
    ),

    [GAME] = LAYOUT_elora_hlc(
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                                  TO(DEFAULT),  TO(DEFAULT),  TO(DEFAULT),  TO(DEFAULT),  TO(DEFAULT),  TO(DEFAULT),
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                                  TO(DEFAULT),  TO(DEFAULT),  TO(DEFAULT),  TO(DEFAULT),  TO(DEFAULT),  TO(DEFAULT),
     TO(DEFAULT),  KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                                  TO(DEFAULT),  TO(DEFAULT),  TO(DEFAULT),  TO(DEFAULT),  TO(DEFAULT),  TO(DEFAULT),
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,          TO(DEFAULT),  TO(DEFAULT),  TO(DEFAULT),  TO(DEFAULT),  TO(DEFAULT),  TO(DEFAULT),  TO(DEFAULT),  TO(DEFAULT),
                                               KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,          TO(DEFAULT),  TO(DEFAULT),  TO(DEFAULT),  TO(DEFAULT),  TO(DEFAULT),
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                                                              KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO
    ),

    [FUNCTION] = LAYOUT_elora_hlc(
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                                  KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_NO,        KC_F9,        KC_F10,       KC_F11,       KC_F12,       KC_NO,                                                                  KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     TO(DEFAULT),  KC_F5,        KC_F6,        KC_F7,        KC_F8,        KC_NO,                                                                  KC_NO,        KC_LALT,      KC_LGUI,      KC_LSFT,      KC_LCTL,      KC_NO,
     KC_NO,        KC_F1,        KC_F2,        KC_F3,        KC_F4,        KC_NO,        KC_NO,        KC_NO,          KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        HT_MAGIC,
                                               KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,          KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                                                              KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO
    ),

    [MAGIC] = LAYOUT_elora_hlc(
     TO(DEFAULT),  TO(LOWER),    TO(SYMBOL),   TO(GAME),     TO(FUNCTION), KC_NO,                                                                  KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                                  KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                                  RM_TOGG,      RM_SATU,      RM_HUEU,      RM_VALU,      RM_NEXT,      KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,          KC_NO,        KC_NO,        KC_NO,        RM_SATD,      RM_HUED,      RM_VALD,      RM_PREV,      HT_MAGIC,
                                               KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,          KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                                                              KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO
    ),

    [MOUSE] = LAYOUT_elora_hlc(
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                                  KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_NO,        MO_SSLOW,     MO_SMED,      MO_SFAST,     MO_SBLAZING,  KC_NO,                                                                  KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_ESC,       KC_NO,        MS_BTN3,      MS_BTN2,      MS_BTN1,      KC_NO,                                                                  KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,          KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
                                               KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,          KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                                                              KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO
    ),
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

        case HT_LOWER:
            if (record->event.pressed) {
                cw_timer = timer_read();
                layer_on(LOWER);
            } else {
                if (timer_elapsed(cw_timer) >= TAPPING_TERM) {
                    layer_off(LOWER);
                }
            }
            return false;

        case MO_SSLOW:
            pointing_device_set_cpi(200);
            return false;
        case MO_SMED:
            pointing_device_set_cpi(400);
            return false;
        case MO_SFAST:
            pointing_device_set_cpi(800);
            return false;
        case MO_SBLAZING:
            pointing_device_set_cpi(1200);
            return false;
    }
    return true;
}

void keyboard_post_init_user(void) {
    pointing_device_set_cpi(400);
}

#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
void pointing_device_init_user(void) {
    set_auto_mouse_layer(MOUSE);
    set_auto_mouse_enable(true);
}
#endif /* ifdef  */
