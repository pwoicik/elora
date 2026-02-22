#pragma once

#include "td_util.h"

enum {
    TD_MAGIC,
};

TD_FINISHED_FUNC_PROTO(magic_dance_finished);
TD_RESET_FUNC_PROTO(magic_dance_reset);

#define TAP_DANCES \
    [TD_MAGIC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, magic_dance_finished, magic_dance_reset)
