#ifndef SUSPENSIONRT_COMMON_H
#define SUSPENSIONRT_COMMON_H

#include <cstdint>
#include <lvgl.h>

const uint8_t N_WHEELS = 4;
typedef uint16_t length_t;
typedef uint32_t mstime_t;

static const char * BUTTON_MAP_NUMERIC[] = {
    "1", "2", "3", "\n",
    "4", "5", "6", "\n",
    "7", "8", "9", "\n",
    LV_SYMBOL_BACKSPACE, "0", LV_SYMBOL_NEW_LINE, ""
};

#endif
