# This adds module functionality to your keyboard (files found in users/halcyon_modules)
USER_NAME := halcyon_modules

TAP_DANCE_ENABLE = yes
CAPS_WORD_ENABLE = yes
MOUSEKEY_ENABLE = yes
RAW_ENABLE = yes

SRC += hid.c
SRC += trackpad.c
SRC += keys.c
SRC += td_util.c
SRC += td.c

ifdef HLC_TFT_DISPLAY
	SRC += display.c
	SRC += graphics/retron2000_36.qff.c
endif
