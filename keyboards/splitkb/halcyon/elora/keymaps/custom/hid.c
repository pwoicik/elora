#include "hid.h"

#include <stdint.h>

#include "action_layer.h"
#include "raw_hid.h"
#include "usb_descriptor.h"

void send_hid_event(event_t event) {
    static uint8_t buf[RAW_EPSIZE];
    memset(buf, 0, RAW_EPSIZE);
    buf[0] = (uint8_t)event.type;
    switch (event.type) {
        case EVENT_TYPE_LAYER_CHANGED: {
            buf[1] = event.layer;
        } break;
    }
    raw_hid_send(buf, RAW_EPSIZE);
}

// NOLINTNEXTLINE(readability-non-const-parameter)
void raw_hid_receive(uint8_t* data, uint8_t length) {
    if (length != RAW_EPSIZE) {
        return;
    }
    command_type_t type = data[0];
    switch (type) {
        case COMMAND_TYPE_CHANGE_LAYER: {
            uint8_t layer = data[1];
            if (layer == 0) {
                layer_clear();
            } else {
                layer_move(layer);
            }
        } break;
    }
}
