#include <stdint.h>

#include "color.h"
#include "graphics/retron2000_36.qff.h"
#include "hlc_tft_display/config.h"
#include "hlc_tft_display/graphics/fonts/Retron2000-27.qff.h"
#include "hlc_tft_display/graphics/fonts/Retron2000-underline-27.qff.h"
#include "hlc_tft_display/hlc_tft_display.h"
#include "qp.h"

static painter_font_handle_t retron27;
static painter_font_handle_t retron27_underline;
static painter_font_handle_t retron36;

painter_device_t lcd;
painter_device_t lcd_surface;

layer_state_t m_last_layer_state = {0};
uint8_t       m_last_mods_state  = 0;

static const char* mod_ctrl  = "c";
static const char* mod_shift = "s";
static const char* mod_alt   = "a";
static const char* mod_gui   = "g";

typedef struct {
    char*    name;
    hsv_t    color;
    uint16_t text_width;
} layer_display_t;

// NOLINTBEGIN(readability-magic-numbers)
static layer_display_t layer_display_data[] = {
    {"BASE", {236, 135, 255}, 0},
    {"BASE", {236, 135, 255}, 0},
    {"LOW", {141, 175, 255}, 0},
    {"SYM", {192, 115, 255}, 0},
    {"FUNC", {104, 155, 255}, 0},
    {"MAG", {46, 195, 255}, 0},
    {"GAME", {27, 175, 255}, 0},
    {"MOUS", {0, 175, 255}, 0},
};
// NOLINTEND(readability-magic-numbers)

bool module_post_init_user(void) {
    retron27           = qp_load_font_mem(font_Retron2000_27);
    retron27_underline = qp_load_font_mem(font_Retron2000_underline_27);
    retron36           = qp_load_font_mem(font_retron2000_36);

    for (unsigned long i = 0; i < sizeof(layer_display_data) / sizeof(layer_display_t); i++) {
        uint16_t text_width = (uint16_t)qp_textwidth(retron36, layer_display_data[i].name);
        layer_display_data[i].text_width = text_width;
    }

    return false;
}

// NOLINTBEGIN(readability-magic-numbers)
bool display_module_housekeeping_task_user(bool second_display) {
    (void)second_display;

    static bool     first_run_layer = false;
    static bool     first_run_led   = false;
    static bool     first_run_decor = false;
    static uint32_t last_anim       = 0;

    uint16_t layer_y_offset = 10;
    if (m_last_layer_state != layer_state || first_run_layer == false) {
        uint8_t layer = get_highest_layer(layer_state | default_layer_state);

        layer_display_t layer_display = layer_display_data[layer];
        qp_rect(
            lcd_surface,
            0,
            layer_y_offset,
            LCD_WIDTH - 1,
            layer_y_offset + retron27->line_height + 1,
            HSV_BLACK,
            true
        );
        qp_drawtext_recolor(
            lcd_surface,
            (LCD_WIDTH - layer_display.text_width) / 2,
            layer_y_offset,
            retron36,
            layer_display.name,
            layer_display.color.h,
            layer_display.color.s,
            layer_display.color.v,
            HSV_BLACK
        );
        m_last_layer_state = layer_state;
        first_run_layer    = true;
    }

    uint16_t mods_y_offset = LCD_HEIGHT - retron27->line_height - 10;
    uint8_t  mods          = get_mods() | get_oneshot_mods() | get_weak_mods();
    if (first_run_led == false || m_last_mods_state != mods) {
        uint16_t x_offset = 12;
        uint16_t spacing  = 30;

        if (mods & MOD_MASK_CTRL) {
            qp_drawtext_recolor(
                lcd_surface,
                x_offset,
                mods_y_offset,
                retron27_underline,
                mod_ctrl,
                HSV_RED,
                HSV_BLACK
            );
        } else {
            qp_drawtext_recolor(
                lcd_surface, x_offset, mods_y_offset, retron27, mod_ctrl, HSV_CAPS_OFF, HSV_BLACK
            );
        }
        if (mods & MOD_MASK_SHIFT) {
            qp_drawtext_recolor(
                lcd_surface,
                x_offset + spacing,
                mods_y_offset,
                retron27_underline,
                mod_shift,
                HSV_GREEN,
                HSV_BLACK
            );
        } else {
            qp_drawtext_recolor(
                lcd_surface,
                x_offset + spacing,
                mods_y_offset,
                retron27,
                mod_shift,
                HSV_CAPS_OFF,
                HSV_BLACK
            );
        }
        if (mods & MOD_MASK_GUI) {
            qp_drawtext_recolor(
                lcd_surface,
                x_offset + (spacing * 2),
                mods_y_offset,
                retron27_underline,
                mod_gui,
                HSV_BLUE,
                HSV_BLACK
            );
        } else {
            qp_drawtext_recolor(
                lcd_surface,
                x_offset + (spacing * 2),
                mods_y_offset,
                retron27,
                mod_gui,
                HSV_CAPS_OFF,
                HSV_BLACK
            );
        }
        if (mods & MOD_MASK_ALT) {
            qp_drawtext_recolor(
                lcd_surface,
                x_offset + (spacing * 3),
                mods_y_offset,
                retron27_underline,
                mod_alt,
                HSV_YELLOW,
                HSV_BLACK
            );
        } else {
            qp_drawtext_recolor(
                lcd_surface,
                x_offset + (spacing * 3),
                mods_y_offset,
                retron27,
                mod_alt,
                HSV_CAPS_OFF,
                HSV_BLACK
            );
        }

        m_last_mods_state = mods;
        first_run_led     = true;
    }

    if (timer_elapsed32(last_anim) > 33) {
        uint16_t line_padding = 5;
        uint16_t upper_line_y = layer_y_offset + retron36->line_height + line_padding;
        uint16_t lower_line_y = mods_y_offset - line_padding;

        // Clear the area between lines
        qp_rect(lcd_surface, 0, upper_line_y + 1, LCD_WIDTH - 1, lower_line_y - 1, HSV_BLACK, true);

        // Animation logic: a simple bouncing bar
        static int16_t anim_y = 0;
        static int8_t  dir    = 1;
        uint16_t       range  = lower_line_y - upper_line_y - 5;

        anim_y += dir;
        if (anim_y >= range || anim_y <= 0) {
            dir *= -1;
        }

        qp_rect(lcd_surface, 20, upper_line_y + 2 + anim_y, LCD_WIDTH - 21, upper_line_y + 4 + anim_y, 145, 235, 155, true);

        last_anim = timer_read32();
    }

    if (!first_run_decor) {
        uint16_t line_padding = 5;
        uint16_t upper_line_y = layer_y_offset + retron36->line_height + line_padding;
        qp_line(lcd_surface, 0, upper_line_y, LCD_WIDTH, upper_line_y, HSV_WHITE);
        uint16_t lower_line_y = mods_y_offset - line_padding;
        qp_line(lcd_surface, 0, lower_line_y, LCD_WIDTH, lower_line_y, HSV_WHITE);
        first_run_decor = true;
    }

    qp_surface_draw(lcd_surface, lcd, 0, 0, 0);
    return false;
}
// NOLINTEND(readability-magic-numbers)
