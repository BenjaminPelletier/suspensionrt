#include "screen_wheel.h"

#include <Arduino.h>
#include "intrascreen.h"
#include "../ui/ui.h"
#include "../wheels.h"

const uint8_t MAX_SATELLITES = 4;

struct SatelliteUIElements {
    lv_obj_t* chkSatellite;
    lv_obj_t* lblSatellite;
};

struct SatelliteUIState {
    bool toggle;
};

SatelliteUIElements satellite_ui_elements[MAX_SATELLITES];
SatelliteUIState satellite_ui_state[MAX_SATELLITES];

static uint8_t ui_senders[MAX_SATELLITES] = {0, 1, 2, 3};

void set_selected_wheel(uint8_t w) {
    lv_dropdown_set_selected(ui_ddSelectedWheel, w);
    Wheel* wheel = get_wheel(w);
    if (wheel != nullptr) {
        for (uint8_t s = 0; s < MAX_SATELLITES; s++) {
            Satellite* satellite = get_satellite_by_index(s);
            if (wheel->satellite == satellite) {
                lv_obj_add_state(satellite_ui_elements[s].chkSatellite, LV_STATE_CHECKED);
            } else {
                lv_obj_remove_state(satellite_ui_elements[s].chkSatellite, LV_STATE_CHECKED);
            }
        }
    }
}

void scrWheel_Loaded(lv_event_t* e) {
    for (uint8_t s = 0; s < MAX_SATELLITES; s++) {
        Satellite* satellite = get_satellite_by_index(s);
        lv_obj_update_flag(satellite_ui_elements[s].chkSatellite, LV_OBJ_FLAG_HIDDEN, satellite == nullptr);
        if (satellite != nullptr) {
            lv_checkbox_set_text(satellite_ui_elements[s].chkSatellite, satellite->id);
        }
    }
    set_selected_wheel(current_wheel);
}

void btnWheelBack_Click(lv_event_t* e) {
    lv_disp_load_scr(ui_scrMain);
}

void ddSelectedWheel_ValueChanged(lv_event_t* e) {
    uint32_t index = lv_dropdown_get_selected(ui_ddSelectedWheel);
    Wheel* wheel = get_wheel(index);
    if (wheel != nullptr) {
        set_selected_wheel(index);
    }
}

void chkSatellite_ValueChanged(lv_event_t* e) {
    uint8_t satellite_index = *(uint8_t*)lv_event_get_user_data(e);
    Satellite* satellite = get_satellite_by_index(satellite_index);
    if (satellite == nullptr) {
        // Should not happen
        Serial.println("Null satellite found in chkSatellite_ValueChanged!");
        return;
    }
    Wheel* wheel = get_wheel(current_wheel);
    wheel->satellite = satellite;
    for (uint8_t s = 0; s < MAX_SATELLITES; s++) {
        if (s == satellite_index) {
            lv_obj_add_state(satellite_ui_elements[s].chkSatellite, LV_STATE_CHECKED);
        } else {
            lv_obj_remove_state(satellite_ui_elements[s].chkSatellite, LV_STATE_CHECKED);
        }
    }
}

void init_wheel_screen_behavior() {
    satellite_ui_elements[0] = {
        .chkSatellite = ui_chkSatellite1,
        .lblSatellite = ui_lblSatellite1,
    };
    satellite_ui_elements[1] = {
        .chkSatellite = ui_chkSatellite2,
        .lblSatellite = ui_lblSatellite2,
    };
    satellite_ui_elements[2] = {
        .chkSatellite = ui_chkSatellite3,
        .lblSatellite = ui_lblSatellite3,
    };
    satellite_ui_elements[3] = {
        .chkSatellite = ui_chkSatellite4,
        .lblSatellite = ui_lblSatellite4,
    };
    lv_obj_add_event_cb(ui_scrWheel, scrWheel_Loaded, LV_EVENT_SCREEN_LOADED, NULL);
    lv_obj_add_event_cb(ui_btnWheelBack, btnWheelBack_Click, LV_EVENT_CLICKED, NULL);
    for (uint8_t s = 0; s < MAX_SATELLITES; s++) {
        lv_obj_add_event_cb(satellite_ui_elements[s].chkSatellite, chkSatellite_ValueChanged, LV_EVENT_VALUE_CHANGED, (void*)&ui_senders[s]);
    }
    lv_obj_add_event_cb(ui_ddSelectedWheel, ddSelectedWheel_ValueChanged, LV_EVENT_VALUE_CHANGED, NULL);
}

void wheel_screen_behavior_tick(const mstime_t now) {
    Wheel* wheel = get_wheel(current_wheel);
    if (wheel == nullptr) {
        // This should not happen
        Serial.println("Got wheel == nullptr in wheel_screen_behavior_tick");
    }
    for (uint8_t s = 0; s < MAX_SATELLITES; s++) {
        Satellite* satellite = get_satellite_by_index(s);
        if (satellite == nullptr) { break; }
        if (satellite->t_report > wheel->t_last_report) {
            int dist = satellite->distance;
            char text_buffer[8];

            if (satellite == wheel->satellite) {
                int32_t percent_height;
                if (dist < wheel->fully_compressed_distance) {
                    percent_height = 0;
                } else if (dist > wheel->fully_extended_distance) {
                    percent_height = 100;
                } else {
                    percent_height = (int32_t)100 * (dist - wheel->fully_compressed_distance) / (wheel->fully_extended_distance - wheel->fully_compressed_distance);
                }
                lv_obj_set_height(ui_ctnrGap, lv_pct(percent_height));

                sprintf(text_buffer, "%d", dist);
                lv_label_set_text(ui_lblGap, text_buffer);
            }

            text_buffer[0] = satellite_ui_state[s].toggle ? '/' : '\\';
            sprintf(text_buffer + 1, " %d", dist);
            lv_label_set_text(satellite_ui_elements[s].lblSatellite, text_buffer);
            satellite_ui_state[s].toggle = !satellite_ui_state[s].toggle;
        }
    }
}
