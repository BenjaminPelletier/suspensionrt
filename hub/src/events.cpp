#include <cstdint>
#include <Arduino.h>

#include <lvgl.h>
#include "ui/ui.h"

void onTimeOfFlight(uint8_t sensor, int distance) {
    lv_obj_t* label = NULL;
    if (sensor == 0) {
        label = ui_lblLeftRear;
    } else if (sensor == 1) {
        label = ui_lblLeftFront;
    } else if (sensor == 2) {
        label = ui_lblRightFront;
    } else if (sensor == 3) {
        label = ui_lblRightRear;
    }

    if (label != NULL) {
        char text_buffer[8];
        sprintf(text_buffer, "%d", distance);
        //lv_label_set_text(ui_lblLeftRear, text_buffer);
    }
}
