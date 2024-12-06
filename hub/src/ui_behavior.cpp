#include "ui_behavior.h"

#include <esp32_smartdisplay.h>

#include "common.h"
#include "ui/ui.h"
#include "wheels.h"

mstime_t next_millis;

struct WheelUI {
    lv_obj_t* lblDistance;

    lv_obj_t* ctnrGap;

    lv_obj_t* imgWifi;
    mstime_t last_wifi_toggle;
    bool wifi_visible;
};

const mstime_t WIFI_TOGGLE_PERIOD = 200;

const length_t N_WHEELS = 4;
WheelUI wheel_uis[N_WHEELS];

void init_ui_behavior() {
    wheel_uis[0] = {
        .lblDistance = ui_lblLeftRear,
        .ctnrGap = ui_ctnrLeftRearGap,
        .imgWifi = ui_imgLeftRearWifi,
    };
    wheel_uis[1] = {
        .lblDistance = ui_lblLeftFront,
        .ctnrGap = ui_ctnrLeftFrontGap,
        .imgWifi = ui_imgLeftFrontWifi,
    };
    wheel_uis[2] = {
        .lblDistance = ui_lblRightRear,
        .ctnrGap = ui_ctnrRightRearGap,
        .imgWifi = ui_imgRightRearWifi,
    };
    wheel_uis[3] = {
        .lblDistance = ui_lblRightFront,
        .ctnrGap = ui_ctnrRightFrontGap,
        .imgWifi = ui_imgRightFrontWifi,
    };
}

void ui_behavior_tick(const mstime_t now) {
    char text_buffer[32];

    if (now > next_millis)
    {
        next_millis = now + 500;

        sprintf(text_buffer, "%d", now);
        lv_label_set_text(ui_lblStatus1, text_buffer);

        float light_level = smartdisplay_lcd_adaptive_brightness_cds();
        sprintf(text_buffer, "%.3f", light_level);
        lv_label_set_text(ui_lblStatus2, text_buffer);
    }

    for (uint8_t w = 0; w < N_WHEELS; w++) {
        Wheel* wheel = get_wheel(w);
        if (wheel == nullptr) { continue; }
        if (wheel->satellite == nullptr) {
            lv_label_set_text(wheel_uis[w].lblDistance, "???");
        } else {
            if (wheel->satellite->t_report > wheel->t_last_report) {
                int dist = wheel->satellite->distance;
                sprintf(text_buffer, "%d", dist);
                lv_label_set_text(wheel_uis[w].lblDistance, text_buffer);

                int32_t percent_height;
                if (dist < wheel->fully_compressed_distance) {
                    percent_height = 0;
                } else if (dist > wheel->fully_extended_distance) {
                    percent_height = 100;
                } else {
                    percent_height = (int32_t)100 * (dist - wheel->fully_compressed_distance) / (wheel->fully_extended_distance - wheel->fully_compressed_distance);
                }
                lv_obj_set_height(wheel_uis[w].ctnrGap, lv_pct(percent_height));

                if (now - wheel_uis[w].last_wifi_toggle >= WIFI_TOGGLE_PERIOD) {
                    lv_obj_update_flag(wheel_uis[w].imgWifi, LV_OBJ_FLAG_HIDDEN, wheel_uis[w].wifi_visible);
                    wheel_uis[w].wifi_visible = !wheel_uis[w].wifi_visible;
                    wheel_uis[w].last_wifi_toggle = now;
                }
                wheel->t_last_report = wheel->satellite->t_report;
            }
        }
    }
}
