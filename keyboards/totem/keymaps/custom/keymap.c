#include <stdint.h>

#include "config.h"
#include "default_keyboard.h"
#include "info_config.h"
#include "keycodes.h"
#include "keymap_us.h"
#include "progmem.h"
#include "quantum_keycodes.h"

// NOLINTBEGIN(bugprone-reserved-identifier)
enum layers {
    DEFAULT = 0,
    NAV,
    NUM,
    SYM,
    FUN,
    MOU,
};
// NOLINTEND(bugprone-reserved-identifier)

#define HM_A(key) LALT_T(key)
#define HM_C(key) LCTL_T(key)
#define HM_G(key) LGUI_T(key)
#define HM_S(key) LSFT_T(key)

#define HR_N HM_C(KC_N)
#define HR_Z HM_S(KC_Z)
#define HR_T HM_G(KC_T)
#define HR_S HM_A(KC_S)

#define HR_H HM_A(KC_H)
#define HR_A HM_G(KC_A)
#define HR_E HM_S(KC_E)
#define HR_I HM_C(KC_I)

#define HT_ALT_R RALT_T(KC_R)

#define LT_SYM_ENT LT(SYM, KC_ENT)
#define LT_NAV_BSP LT(NAV, KC_BSPC)
#define LT_NUM_SPC LT(NUM, KC_SPC)
#define LT_FUN_TAB LT(FUN, KC_TAB)
#define LT_MOU_DEL LT(MOU, KC_DEL)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEFAULT] = LAYOUT_v(
    // left ----------------------------------------------------------------------------
                KC_B,       KC_L,       KC_D,       KC_C,       KC_V,
                HR_N,       HR_Z,       HR_T,       HR_S,       KC_G,
    KC_ESC,     KC_X,       KC_Q,       KC_M,       KC_W,       CW_TOGG,
                                                    LT_MOU_DEL, LT_NUM_SPC, LT_NAV_BSP,
    // right ---------------------------------------------------------------------------
                KC_J,       KC_F,       KC_O,       KC_U,       KC_SCLN,
                KC_Y,       HR_H,       HR_A,       HR_E,       HR_I,
                KC_K,       KC_P,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_QUOT,
    LT_SYM_ENT, HT_ALT_R, LT_FUN_TAB
    ),

    [NAV] = LAYOUT_v(
    // left ----------------------------------------------------------------------------
                KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
                KC_LCTL,    KC_LSFT,    KC_LGUI,    KC_LALT,    KC_NO,
    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
                                                    KC_NO,      KC_NO,      KC_NO,
    // right ---------------------------------------------------------------------------
                KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
                KC_NO,      KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT,
                KC_INS,     KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END,     KC_NO,
    KC_ENT,     KC_BSPC,    KC_DEL
    ),

    [NUM] = LAYOUT_v(
                KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
                KC_LCTL,    KC_LSFT,    KC_LGUI,    KC_LALT,    KC_NO,
    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
                                                    KC_NO,      KC_NO,      KC_NO,

                KC_LBRC,    KC_7,       KC_8,       KC_9,       KC_RBRC,
                KC_MINS,    KC_4,       KC_5,       KC_6,       KC_EQL,
                KC_SCLN,    KC_1,       KC_2,       KC_3,       KC_BSLS,    KC_GRV,
    KC_COMM,    KC_0,       KC_DOT
    ),

    [SYM] = LAYOUT_v(
    // left ----------------------------------------------------------------------------
                KC_LCBR,    KC_LPRN,    KC_RPRN,    KC_RCBR,    KC_EXLM,
                KC_CIRC,    KC_AMPR,    KC_PERC,    KC_DLR,     KC_PLUS,
    KC_BSLS,    KC_LT,      KC_PIPE,    KC_MINS,    KC_GT,      KC_ASTR,
                                                    KC_TILD,    KC_EQL,     KC_UNDS,
    // right ---------------------------------------------------------------------------
                KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
                KC_GRV,     KC_LALT,    KC_LGUI,    KC_LSFT,    KC_LCTL,
                KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
    KC_NO,      KC_NO,      KC_NO
    ),

    [FUN] = LAYOUT_v(
    // left ----------------------------------------------------------------------------
                KC_F12,     KC_F7,      KC_F8,      KC_F9,      KC_PSCR,
                KC_F11,     KC_F4,      KC_F5,      KC_F6,      KC_PAUSE,
    KC_NO,      KC_F10,     KC_F1,      KC_F2,      KC_F3,      KC_NO,
                                                    KC_NO,      KC_TAB,     KC_SPC,
    // right ---------------------------------------------------------------------------
                KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
                KC_NO,      KC_LALT,    KC_LGUI,    KC_LSFT,    KC_LCTL,
                KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
    KC_NO,      KC_NO,      KC_NO
    ),

    [MOU] = LAYOUT_v(
    // left ----------------------------------------------------------------------------
                KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
                KC_LCTL,    KC_LSFT,    KC_LGUI,    KC_LALT,    KC_NO,
    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
                                                    KC_NO,      KC_NO,      KC_NO,
    // right ---------------------------------------------------------------------------
                MS_ACL0,    KC_NO,      KC_NO,      KC_NO,      KC_NO,
                MS_ACL1,    MS_LEFT,    MS_DOWN,    MS_UP,      MS_RGHT,
                MS_ACL2,    MS_WHLL,    MS_WHLD,    MS_WHLU,    MS_WHLR,    KC_NO,
    MS_BTN1,    MS_BTN2,    MS_BTN3
    ),

    /*
    [DEFAULT] = LAYOUT_v(
    // left ----------------------------------------------------------------------------
                KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
                KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
                                                    KC_NO,      KC_NO,      KC_NO,
    // right ---------------------------------------------------------------------------
                KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
                KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
                KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
    KC_NO,      KC_NO,      KC_NO
    ),
    */
};
// clang-format on

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

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t* record) {
    (void)record;
    switch (keycode) {
        case HT_ALT_R:
            return 0;
        default:
            return QUICK_TAP_TERM;
    }
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
