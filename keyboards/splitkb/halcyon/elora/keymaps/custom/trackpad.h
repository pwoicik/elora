#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "action.h"

enum {
    CPI_LEVEL_SLOW    = 200,
    CPI_LEVEL_MEDIUM  = 400,
    CPI_LEVEL_FAST    = 800,
    CPI_LEVEL_BLAZING = 1200,
};
typedef uint16_t cpi_level_t;

void init_trackpad(void);

bool set_trackpad_cpi(cpi_level_t cpi, keyrecord_t* record);
