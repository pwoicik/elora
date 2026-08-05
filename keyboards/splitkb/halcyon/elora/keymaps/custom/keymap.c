#include "action_layer.h"
#include "action_util.h"
#include "hid.h"
#include "keycodes.h"
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
     KC_GRV,       KC_X,         KC_Q,         KC_M,         KC_W,         CW_TOGG,      KC_NO,        KC_NO,
                                               KC_NO,        KC_NO,        KC_DEL,       LT_NUM_SPC,   LT_NAV_BSP,
     // RIGHT HALF --------------------------------------------------------------------------------------------
                                 KC_6,         KC_7,         KC_8,         KC_9,         KC_0,         KC_MINS,
                                 KC_J,         KC_F,         KC_O,         KC_U,         KC_SCLN,      KC_BSLS,
                                 KC_Y,         HM_A(KC_H),   HM_G(KC_A),   HM_S(KC_E),   HM_C(KC_I),   KC_QUOT,
     KC_NO,        KC_NO,        KC_K,         KC_P,         KC_COMM,      KC_DOT,       KC_SLSH,      TD(TD_MAGIC),
     LT_SYM_ENT,   HT_ALT_R,     LT_FUN_TAB,   KC_NO,        KC_NO
    ),

    [NAVIGATION] = ELORA_LAYOUT(
     // LEFT HALF ---------------------------------------------------------------------------------------------
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_HOME,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_END,
     KC_NO,        KC_LCTL,      KC_LSFT,      KC_LGUI,      KC_LALT,      KC_PGUP,
     KC_NO,        KC_NO,        KC_NO,        KC_DOWN,      KC_NO,        KC_PGDN,      KC_NO,        KC_NO,
                                               KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     // RIGHT HALF --------------------------------------------------------------------------------------------
                                 KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
                                 KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
                                 KC_NO,        KC_LEFT,      KC_DOWN,      KC_UP,        KC_RIGHT,     KC_NO,
     KC_NO,        KC_NO,        KC_INS,       KC_HOME,      KC_PGDN,      KC_PGUP,      KC_END,       KC_NO,
     KC_ENT,       KC_BSPC,      KC_DEL,       KC_NO,        KC_NO
    ),

    [NUMBER] = ELORA_LAYOUT(
     // LEFT HALF ---------------------------------------------------------------------------------------------
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_HOME,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_END,
     KC_NO,        KC_LCTL,      KC_LSFT,      KC_LGUI,      KC_LALT,      KC_PGUP,
     KC_NO,        KC_NO,        KC_NO,        KC_DOWN,      KC_NO,        KC_PGDN,      KC_NO,        KC_NO,
                                               KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     // RIGHT HALF --------------------------------------------------------------------------------------------
                                 KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
                                 KC_LBRC,      KC_7,         KC_8,         KC_9,         KC_RBRC,      KC_NO,
                                 KC_MINS,      KC_4,         KC_5,         KC_6,         KC_EQL,       KC_NO,
     KC_NO,        KC_NO,        KC_SCLN,      KC_1,         KC_2,         KC_3,         KC_BSLS,      KC_GRV,
     KC_COMM,      KC_0,         KC_DOT,       KC_NO,        KC_NO
    ),

    [SYMBOL] = ELORA_LAYOUT(
     // LEFT HALF ---------------------------------------------------------------------------------------------
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_NO,        KC_LCBR,      KC_LPRN,      KC_RPRN,      KC_RCBR,      KC_EXLM,
     KC_NO,        KC_CIRC,      KC_AMPR,      KC_PERC,      KC_DLR,       KC_PLUS,
     KC_BSLS,      KC_LT,        KC_PIPE,      KC_MINS,      KC_GT,        KC_ASTR,      KC_NO,        KC_NO,
                                               KC_NO,        KC_NO,        KC_TILD,      KC_EQL,       KC_UNDS,
     // RIGHT HALF --------------------------------------------------------------------------------------------
                                 KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
                                 KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
                                 KC_GRV,       KC_LALT,      KC_LGUI,      KC_LSFT,      KC_LCTL,      KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO
    ),

    [FUNCTION] = ELORA_LAYOUT(
     // LEFT HALF ---------------------------------------------------------------------------------------------
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_NO,        KC_F12,       KC_F7,        KC_F8,        KC_F9,        KC_PSCR,
     KC_NO,        KC_F11,       KC_F4,        KC_F5,        KC_F6,        KC_PAUSE,
     KC_NO,        KC_F10,       KC_F1,        KC_F2,        KC_F3,        KC_NO,        KC_NO,        KC_NO,
                                               KC_NO,        KC_NO,        KC_NO,        KC_TAB,       KC_SPC,
     // RIGHT HALF --------------------------------------------------------------------------------------------
                                 KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
                                 KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
                                 KC_GRV,       KC_LALT,      KC_LGUI,      KC_LSFT,      KC_LCTL,      KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO
    ),

    [MAGIC] = ELORA_LAYOUT(
     // LEFT HALF ---------------------------------------------------------------------------------------------
     KC_NO,        KC_NO,        KC_NO,        TO(GAME),     KC_NO,        KC_NO,
     KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
     KC_NO,        DF(DEFAULT),  KC_NO,        KC_NO,        KC_NO,        KC_NO,
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
                                               KC_M,         KC_T,         KC_X,         KC_SPC,       KC_DEL,
     // RIGHT HALF --------------------------------------------------------------------------------------------
                                 KC_F1,        KC_F2,        KC_F3,        KC_F4,        KC_F5,        KC_F6,
                                 KC_6,         KC_7,         KC_8,         KC_9,         KC_0,         KC_NO,
                                 KC_H,         KC_LEFT,      KC_UP,        KC_RIGHT,     KC_L,         KC_NO,
     KC_NO,        KC_NO,        KC_Y,         KC_PGDN,      KC_DOWN,      KC_PGUP,      KC_NO,        TO_DEF,
     KC_ENT,       KC_NO,        KC_N,         KC_O,         KC_P
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
