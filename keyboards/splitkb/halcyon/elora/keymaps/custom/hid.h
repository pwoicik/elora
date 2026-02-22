#pragma once

#include <stdint.h>

typedef enum {
    EVENT_TYPE_LAYER_CHANGED,
} event_type_t;

typedef struct {
    event_type_t type;
    union {
        uint8_t layer;
    };
} event_t;

typedef enum {
    COMMAND_TYPE_CHANGE_LAYER,
} command_type_t;

void send_hid_event(event_t event);
