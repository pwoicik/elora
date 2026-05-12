#include "action_layer.h"
#include "action_util.h"
#include "hid.h"
#include "keys.h"
#include "layers.h"
#include "layout.h"
#include "td.h"
#include "trackpad.h"

void keyboard_post_init_user(void) {
    init_trackpad();
}

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t cur_layer = get_highest_layer(state);
    if (cur_layer == get_highest_layer(default_layer_state)) {
        sticky_mods = 0;
        clear_weak_mods();
        send_keyboard_report();
    } else if (sticky_mods_ != 0) {
        sticky_mods = sticky_mods_;
        activate_sticky_mods();
    }
    send_hid_event((event_t){.type = EVENT_TYPE_LAYER_CHANGED, .layer = cur_layer});
    return state;
}

tap_dance_action_t tap_dance_actions[] = {TAP_DANCES};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEFAULT] = ELORA_LAYOUT(
     // LEFT HALF ---------------------------------------------------------------------------------------------
     KC_EQL,       KC_1,         KC_2,         KC_3,         KC_4,         KC_5,
     KC_TAB,       KC_B,         KC_L,         KC_D,         KC_C,         KC_V,
     KC_ESC,       HM_C(KC_N),   HM_S(KC_Z),   HM_G(KC_T),   HM_A(KC_S),   KC_G,
     KC_GRV,       KC_X,         KC_Q,         KC_M,         KC_W,         KC_NO,        CW_SFT,       KC_DEL,
                                               KC_NO,        MO(FUNCTION), MO(LOWER),    KC_SPC,       KC_BSPC,
     // RIGHT HALF --------------------------------------------------------------------------------------------
                                 KC_6,         KC_7,         KC_8,         KC_9,         KC_0,         KC_MINS,
                                 KC_J,         KC_F,         KC_O,         KC_U,         SEMI,         KC_BSLS,
                                 KC_Y,         HM_A(KC_H),   HM_G(KC_A),   HM_S(KC_E),   HM_C(KC_I),   KC_QUOT,
     MO(FUNCTION), CW_SFT,       KC_K,         KC_P,         KC_COMM,      KC_DOT,       KC_SLSH,      TD(TD_MAGIC),
     HT_SYM ,      HT_ALT_R,     MO(LOWER),    MO(FUNCTION), KC_NO
    ),

    [QWERTY] = ELORA_LAYOUT(
     // LEFT HALF ---------------------------------------------------------------------------------------------
     KC_EQL,       KC_1,         KC_2,         KC_3,         KC_4,         KC_5,
     KC_TAB,       KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,
     KC_ESC,       HM_C(KC_A),   HM_S(KC_S),   HM_G(KC_D),   HM_A(KC_F),   KC_G,
     KC_GRV,       KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,         CW_SFT,       KC_DEL,
                                               KC_NO,        MO(FUNCTION), MO(LOWER),    KC_SPC,       KC_BSPC,
     // RIGHT HALF --------------------------------------------------------------------------------------------
                                 KC_6,         KC_7,         KC_8,         KC_9,         KC_0,         KC_MINS,
                                 KC_Y,         KC_U,         KC_I,         KC_O,         KC_P,         KC_BSLS,
                                 KC_H,         HM_A(KC_J),   HM_G(KC_K),   HM_S(KC_L),   HM_C(SEMI),   KC_QUOT,
     MO(FUNCTION), CW_SFT,       KC_N,         KC_M,         KC_COMM,      KC_DOT,       KC_SLSH,      TD(TD_MAGIC),
     HT_SYM ,      KC_RALT,      MO(LOWER),    MO(FUNCTION), KC_NO
    ),

    [LOWER] = ELORA_LAYOUT(
     // LEFT HALF ---------------------------------------------------------------------------------------------
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_HOME,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_END,
     KC_NO,        KC_NO,        KC_LEFT,      KC_UP,        KC_RIGHT,     KC_PGUP,
     KC_NO,        KC_NO,        KC_NO,        KC_DOWN,      KC_NO,        KC_PGDN,      KC_NO,        KC_DEL,
                                               KC_NO,        KC_NO,        KC_NO,        KC_SPC,       KC_BSPC,
     // RIGHT HALF --------------------------------------------------------------------------------------------
                                 KC_LPRN,      KC_NUM,       KC_PEQL,      KC_PSLS,      KC_PAST,      KC_NO,
                                 KC_RPRN,      KC_P7,        KC_P8,        KC_P9,        KC_PMNS,      KC_PSCR,
                                 KC_PERC,      HM_A(KC_P4),  HM_G(KC_P5),  HM_S(KC_P6),  HM_C(KC_PPLS),KC_NO,
     KC_NO,        KC_NO,        KC_COMM,      KC_P1,        KC_P2,        KC_P3,        KC_PENT,      TD(TD_MAGIC),
     KC_ENT,       KC_NO,        KC_P0,        KC_PDOT,      KC_NO
    ),

    [SYMBOL] = ELORA_LAYOUT(
     // LEFT HALF ---------------------------------------------------------------------------------------------
     KC_GRAVE,     KC_LBRC,      KC_LPRN,      KC_RPRN,      KC_RBRC,      KC_DOT,
     KC_EXLM,      KC_COMM,      KC_LCBR,      KC_RCBR,      KC_SCLN,      KC_QUES,
     KC_HASH,      KC_CIRC,      KC_EQL,       KC_UNDS,      KC_DOLLAR,    KC_ASTR,
     KC_TILDE,     KC_LT,        KC_PIPE,      KC_MINS,      KC_GT,        KC_SLSH,      KC_BSLS,      KC_AT,
                                               KC_NO,        KC_AMPR,      KC_PLUS,      KC_PERC,      KC_COLON,
     // RIGHT HALF --------------------------------------------------------------------------------------------
                                 KC_NO,        KC_NUM,       KC_PEQL,      KC_PSLS,      KC_PAST,      KC_NO,
                                 KC_GRAVE,     KC_P7,        KC_P8,        KC_P9,        KC_PMNS,      KC_PSCR,
                                 KC_DQT,       KC_P4,        KC_P5,        KC_P6,        KC_PPLS,      KC_NO,
     KC_NO,        KC_NO,        KC_QUOT,      KC_P1,        KC_P2,        KC_P3,        KC_PENT,      TD(TD_MAGIC),
     KC_NO,        KC_NO,        KC_P0,        KC_PDOT,      KC_NO
    ),

    [FUNCTION] = ELORA_LAYOUT(
     // LEFT HALF ---------------------------------------------------------------------------------------------
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_NO,        KC_F9,        KC_F10,       KC_F11,       KC_F12,       KC_NO,
     TO_DEF,       KC_F5,        KC_F6,        KC_F7,        KC_F8,        KC_NO,
     KC_NO,        KC_F1,        KC_F2,        KC_F3,        KC_F4,        KC_NO,        KC_NO,        KC_NO,
                                               KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     // RIGHT HALF --------------------------------------------------------------------------------------------
                                 KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
                                 KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
                                 KC_NO,        KC_LALT,      KC_LGUI,      KC_LSFT,      KC_LCTL,      KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        TD(TD_MAGIC),
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO
    ),

    [MAGIC] = ELORA_LAYOUT(
     // LEFT HALF ---------------------------------------------------------------------------------------------
     KC_NO,        KC_NO,        KC_NO,        TO(GAME),     KC_NO,        KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_NO,        DF(DEFAULT),  DF(QWERTY),   KC_NO,        KC_NO,        KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
                                               KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     // RIGHT HALF --------------------------------------------------------------------------------------------
                                 KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
                                 KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
                                 RM_TOGG,      RM_SATU,      RM_HUEU,      RM_VALU,      RM_NEXT,      KC_NO,
     KC_NO,        KC_NO,        KC_NO,        RM_SATD,      RM_HUED,      RM_VALD,      RM_PREV,      TO_DEF,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO
    ),

    [GAME] = ELORA_LAYOUT(
     // LEFT HALF ---------------------------------------------------------------------------------------------
     KC_ESC,       KC_I,         KC_2,         KC_3,         KC_4,         KC_5,
     KC_F13,       KC_TAB,       KC_Q,         KC_1,         KC_E,         KC_R,
     KC_G,         KC_LSFT,      KC_A,         KC_W,         KC_D,         KC_F,
     KC_B,         KC_LCTL,      KC_Z,         KC_S,         KC_C,         KC_V,         KC_LALT,      KC_ENT,
                                               KC_M,         KC_T,         KC_X,         KC_SPC,       KC_NO,
     // RIGHT HALF --------------------------------------------------------------------------------------------
                                 KC_F1,        KC_F2,        KC_F3,        KC_F4,        KC_F5,        KC_F6,
                                 KC_6,         KC_7,         KC_8,         KC_9,         KC_0,         KC_NO,
                                 KC_H,         KC_Y,         KC_N,         KC_O,         KC_L,         KC_NO,
     MO_DEF,       MO_DEF,       KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        TO_DEF,
     KC_ENT,       MO_DEF,       KC_NO,        KC_NO,        KC_NO
    ),

    [MOUSE] = ELORA_LAYOUT(
     // LEFT HALF ---------------------------------------------------------------------------------------------
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_NO,        MO_SSLOW,     MO_SMED,      MO_SFAST,     MO_SBLAZING,  KC_NO,
     KC_ESC,       KC_LCTL,      KC_LSFT,      KC_LGUI,      KC_LALT,      KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
                                               KC_NO,        KC_NO,        MS_BTN2,      MS_BTN1,      MS_BTN3,
     // RIGHT HALF --------------------------------------------------------------------------------------------
                                 KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
                                 KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
                                 KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO
    ),
};
// clang-format on
