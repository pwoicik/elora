#include "td.h"

#include "action_layer.h"
#include "layers.h"
#include "td_util.h"

TD_FINISHED_FUNC(magic_dance_finished, {
    switch (td_tap_state.state) {
        case TD_SINGLE_HOLD:
        case TD_TRIPLE_TAP:
            layer_on(MAGIC);
            break;

        case TD_DOUBLE_TAP:
            layer_on(GAME);
            break;

        default:
            break;
    }
})

TD_RESET_FUNC(magic_dance_reset, {
    switch (td_tap_state.state) {
        case TD_SINGLE_HOLD:
            layer_off(MAGIC);
            break;

        default:
            break;
    }
})
