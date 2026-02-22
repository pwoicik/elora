#pragma once

#include "process_tap_dance.h"

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

extern td_tap_t td_tap_state;

td_state_t cur_dance(tap_dance_state_t* state);

#define TD_FINISHED_FUNC_PROTO(name) void name(tap_dance_state_t* state, void* user_data)
#define TD_FINISHED_FUNC(name, body)                       \
    void name(tap_dance_state_t* state, void* user_data) { \
        (void)user_data;                                   \
        td_tap_state.state = cur_dance(state);             \
        body;                                              \
    }

#define TD_RESET_FUNC_PROTO(name) void name(tap_dance_state_t* state, void* user_data)
#define TD_RESET_FUNC(name, body)                          \
    void name(tap_dance_state_t* state, void* user_data) { \
        (void)state;                                       \
        (void)user_data;                                   \
        body;                                              \
        td_tap_state.state = TD_NONE;                      \
    }
