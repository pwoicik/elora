#include "trackpad.h"

#include "layers.h"
#include "pointing_device.h"

#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
#    include "pointing_device_auto_mouse.h"
#endif /* ifdef  */

void init_trackpad(void) {
    pointing_device_set_cpi(CPI_LEVEL_FAST);
}

bool set_trackpad_cpi(cpi_level_t cpi, keyrecord_t* record) {
    if (record->event.pressed) {
        pointing_device_set_cpi(cpi);
    }
    return false;
}

void pointing_device_init_user(void) {
#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
    set_auto_mouse_layer(MOUSE);
    set_auto_mouse_enable(true);
#endif /* ifdef  */
}
