#include "td_util.h"

td_tap_t td_tap_state = {
    .is_press_action = true,
    .state           = TD_NONE,
};

td_state_t cur_dance(tap_dance_state_t* state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) {
            return TD_SINGLE_TAP;
        }
        return TD_SINGLE_HOLD;
    }
    if (state->count == 2) {
        if (state->interrupted) {
            return TD_DOUBLE_SINGLE_TAP;
        }
        if (state->pressed) {
            return TD_DOUBLE_HOLD;
        }
        return TD_DOUBLE_TAP;
    }

    if (state->count == 3) {
        if (state->interrupted || !state->pressed) {
            return TD_TRIPLE_TAP;
        }
        return TD_TRIPLE_HOLD;
    }
    return TD_UNKNOWN;
}
